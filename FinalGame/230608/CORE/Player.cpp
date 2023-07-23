#include "stdafx.h"
#include "Player.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "SceneManager.h"
#include "BmpMgr.h"
#include "BitMap.h"
#include "CameraComponent.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "ObjFactory.h"
#include "CameraComponent.h"
#include "UIMgr.h"
#include "SoundMgr.h"


CPlayer::CPlayer()
{
	////////////////
	EDITMODE = false;
	CAMERAMODE = false;
	////////////////

	m_Type = PLAYER;
}

CPlayer::~CPlayer()
{
}


void CPlayer::Initialize(void)
{
	//카메라 추가
	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);
	CCharacter::Initialize();
	//

	m_tInfo = { 600.f, 900.f, 50.f, 50.f };
	m_vInfo.vPos = { WINCX / 2.f, WINCY / 2.f, 0.f };
	m_vInfo.vLook = { 0.f,-1.f,0.f };
	m_vInfo.vDir = m_vInfo.vLook;
	
	m_vPoint.push_back({-100.f,-100.f,0.f});
	m_vPoint.push_back({ 100.f,-100.f,0.f });
	m_vPoint.push_back({ 150.f,0.f,0.f });
	m_vPoint.push_back({ 100.f,100.f,0.f });
	m_vPoint.push_back({ -100.f,100.f,0.f });
	
	for (auto& iter : m_vPoint)
	{
		m_vOriginPoint.push_back(iter);
	}

	m_fAngle = 0.f;
	m_iAdditionJump_MaxCount = 3;
	m_iAdditionJump_Count = m_iAdditionJump_MaxCount;
	m_fAccel = 0.2f;
	m_fSpeed = 7.f;
	m_PlayerSoundCh = 0;

	InitImage();
}

void CPlayer::Update(void)
{
	//카메라 업데이트
	CCharacter::Update();

	//키값 판단
	Key_Input();
	

	//EDIT모드 아닐때
	if (!EDITMODE)
	{
		//중력 적용 + 점프
		Jump();

		//상태 업데이트 (애니메이션 전환)
		StateUpdate();
	}
	
	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vInfo.vPos.x, m_vInfo.vPos.y, 0.f);

	m_vInfo.matWorld = matScale * matRotZ * matTrans;

	
	//vPos,vPoint,RECT,Collide,FrontCollide 업데이트
	CObj::UpdatePoint();
	CObj::Update_Rect();

	CObj::Move_Frame();
}

void CPlayer::LateUpdate(void)
{
}

void CPlayer::Render(HDC hDC)
{
	if (m_fFrontAngle == 0)
	{
		m_FrameMap[m_State].iMotion = 0;
	}
	else if (m_fFrontAngle == PI)
	{
		m_FrameMap[m_State].iMotion = 1;
	}

	//모든 캐릭터,스킬에 필요
	CCharacter::Render(hDC);

	//CObj::FrameRender(hDC);

	//if (g_CollideCheck)
		CObj::CollideRender(hDC);

}

void CPlayer::Release(void)
{
}

void CPlayer::InitImage()
{
	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/images/player/player_idle_11x2.bmp", L"Player_IDLE");
	
	FRAME TempFrame;
	TempFrame.AnimKey = L"Player_IDLE";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 10;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 70;
	TempFrame.iFrameSizeY = 70;

	m_FrameMap.insert({ IDLE, TempFrame });*/

}



void CPlayer::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		m_fAngle -= D3DXToRadian(3.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		m_fAngle += D3DXToRadian(3.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
	{
		D3DXVec3TransformNormal(&m_vInfo.vDir, &m_vInfo.vLook, &m_vInfo.matWorld);
		m_vInfo.vPos += m_vInfo.vDir * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
	{
		D3DXVec3TransformNormal(&m_vInfo.vDir, &m_vInfo.vLook, &m_vInfo.matWorld);
		m_vInfo.vPos -= m_vInfo.vDir * m_fSpeed;
	}

}


/////////////////////////////////////////////////////////////////
void CPlayer::Jump()
{
	float fY = INFINITY;

	bool bLineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo, &fY);

	if (0.f < fY - m_tInfo.fY)
		m_bJump = true;


	if (m_bJump)
	{
		
		if (bLineCol && (fY < m_tInfo.fY - m_fSpeed_Vertical) && m_fSpeed_Vertical < 0.f)
		{
			m_bJump = false;
			m_tInfo.fY = fY;
 			m_iAdditionJump_Count = m_iAdditionJump_MaxCount;
		}
		else
		{
			
		    
		    m_tInfo.fY -= m_fSpeed_Vertical;
		    
		    if (-2.f < m_fSpeed_Vertical && 2.f > m_fSpeed_Vertical)
		    	m_fSpeed_Vertical -= (0.034f * G) * 0.6f;
		    else
		    	m_fSpeed_Vertical -= (0.034f * G) * 1.2f;
		    
		    
			
		}
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY;
		m_fSpeed_Vertical = 0.f;
	}
	
}

/////////////////////////////////////////////////////////////////

//각 객체의 해당 애니메이션 키값 넣어주기
void CPlayer::StateUpdate()
{
	if (m_PrevState != m_State)
	{
		m_FrameMap[m_State].iFrameStart = 0;
		m_FrameMap[m_State].dwTime = GetTickCount64();
	}

	switch (m_State)
	{
	
	}

}


void CPlayer::PlayerPlaySound(TCHAR* _name)
{
	if (m_PlayerSoundCh == 0)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER, SOUND_VOL3);
	else if (m_PlayerSoundCh == 1)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER2, SOUND_VOL3);
	else if (m_PlayerSoundCh == 2)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER3, SOUND_VOL3);
	else if (m_PlayerSoundCh == 3)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER4, SOUND_VOL3);
	else if (m_PlayerSoundCh == 4)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER5, SOUND_VOL3);

	++m_PlayerSoundCh;
	if (m_PlayerSoundCh == 5)
		m_PlayerSoundCh = 0;
}




int CPlayer::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();


	return 0;
}

int CPlayer::OutCollision(CObj* _target)
{
	OBJ_TYPE targetType = _target->Get_Type();

		
	return 0;
}

int CPlayer::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();
	m_vInfo.vPos += _dir;
	return 0;
}




