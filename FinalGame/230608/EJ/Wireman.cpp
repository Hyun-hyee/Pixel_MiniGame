#include "stdafx.h"
#include "Wireman.h"

#include "LineMgr.h"
#include "KeyMgr.h"
#include "SceneManager.h"
#include "BmpMgr.h"
#include "BitMap.h"
#include "CameraComponent.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "CameraComponent.h"
#include "ObjFactory.h"

CWireman::CWireman():
	m_bMove(true)
{
	////////////////
	EDITMODE = false;
	CAMERAMODE = false;
	////////////////

	m_Type = PLAYER;
}

CWireman::~CWireman()
{
}


void CWireman::Initialize(void)
{
	//카메라 추가
	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);
	CCharacter::Initialize();
	//

	m_tInfo = { 0.f, 0.f, 32.f, 44.f };
	m_vInfo.vPos = { ML + MCX * 0.5f,  MT + MCY * 0.9f,  0.f };
	m_vInfo.vLook = { 1.f,0.f,0.f };
	m_vInfo.vDir = m_vInfo.vLook;

	m_vPoint.push_back({ -50.f,-45.5f,0.f });
	m_vPoint.push_back({ 50.f,-45.5f,0.f });
	m_vPoint.push_back({ 50.f,-12.5f,0.f });
	m_vPoint.push_back({ -50.f,-12.5f,0.f });

	for (auto& iter : m_vPoint)
	{
		m_vOriginPoint.push_back(iter);
	}

	m_fAngle = 0.f;
	//m_iAdditionJump_MaxCount = 3;
	//m_iAdditionJump_Count = m_iAdditionJump_MaxCount;

	m_fAccel = 0.2f;
	m_fSpeed = 15.f;
	m_PlayerSoundCh = 0;
	m_State = OBJ_STATE_IDLE;
	m_fFrontAngle = 0;

	InitImage();
}

void CWireman::Update(void)
{
	//카메라 업데이트
	CCharacter::Update();

	//키값 판단
	if(m_bMove)
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

	//CObj::Move_Frame();
	Move_Frame_Reverse();

}

void CWireman::LateUpdate(void)
{
}

void CWireman::Render(HDC hDC)
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

	CObj::FrameRender(hDC);
	
	Plate_Render(hDC);

	//if (g_CollideCheck)
	//CObj::CollideRender(hDC);

}

void CWireman::Release(void)
{
}

void CWireman::InitImage()
{
	FRAME TempFrame;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Player/_Player_idle_38x44.bmp", L"WM_IDLE");
	TempFrame.AnimKey = L"WM_IDLE";
	TempFrame.iFrameStart = 7;
	TempFrame.iOriginStart = 7;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 38;
	TempFrame.iFrameSizeY = 44;

	m_FrameMap.insert({ OBJ_STATE_IDLE, TempFrame });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Player/_Player_Move_36x44.bmp", L"WM_MOVE");
	TempFrame.AnimKey = L"WM_MOVE";
	TempFrame.iFrameStart = 7;
	TempFrame.iOriginStart = 7;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 36;
	TempFrame.iFrameSizeY = 44;

	m_FrameMap.insert({ OBJ_STATE_MOVE, TempFrame });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Player/_Player_Air_42x44.bmp", L"WM_AIR");
	TempFrame.AnimKey = L"WM_AIR";
	TempFrame.iFrameStart = 5;
	TempFrame.iOriginStart = 5;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 42;
	TempFrame.iFrameSizeY = 44;

	m_FrameMap.insert({ OBJ_STATE_AIR, TempFrame });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Player/_Player_Fall.bmp", L"WM_FALL");
	TempFrame.AnimKey = L"WM_FALL";
	TempFrame.iFrameStart = 0;
	TempFrame.iOriginStart = 0;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 32;
	TempFrame.iFrameSizeY = 57;

	m_FrameMap.insert({ OBJ_STATE_AIR, TempFrame });

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Plate.bmp", L"PLATE");
	m_OneImgKey = L"PLATE";
}

void CWireman::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		if (m_vInfo.vPos.x - 50.f > ML)
			m_vInfo.vPos.x -= m_fSpeed;
		else
			PlayerPlaySound(L"Fall_Effect.wav");
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		if (m_vInfo.vPos.x + 50.f < MR)
		m_vInfo.vPos.x +=  m_fSpeed;
		else
			PlayerPlaySound(L"Fall_Effect.wav");

	}

}


/////////////////////////////////////////////////////////////////
void CWireman::Jump()
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
void CWireman::StateUpdate()
{
	if (m_PrevState != m_State)
	{
		m_FrameMap[m_State].iFrameStart = m_FrameMap[m_State].iOriginStart;
		m_FrameMap[m_State].dwTime = GetTickCount64();
	}

	switch (m_State)
	{

	}

}

void CWireman::Plate_Render(HDC hDC)
{
	//카메라 위치(디폴트 -> 플레이어)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(m_OneImgKey);

	Gdiplus::Bitmap* pImage;

	//사용할 이미지 Key 가져오기
	pImage = pBitMap->Get_Image();

	Gdiplus::Graphics g(hDC);

	//이미지 출력 (빠름, 알파블랜딩 X)
	g.DrawImage(pImage,
		Gdiplus::Rect(
			((int)(m_vPoint[0].x) - ((int)cameraPos.x - (ML + MCX / 2))),
			((int)(m_vPoint[0].y) - ((int)cameraPos.y - (MT + MCY / 2))),
			100.f,  //복사 사이즈
			33.f //복사 사이즈
		),
		0,
		0,
		pImage->GetWidth(),
		pImage->GetHeight(), //이미지 원본 사이즈
		Gdiplus::UnitPixel);

}

void CWireman::Move_Frame_Reverse()
{
	if (m_FrameMap[m_State].dwTime + m_FrameMap[m_State].dwSpeed < GetTickCount64())
	{
		--m_FrameMap[m_State].iFrameStart;

		if (m_FrameMap[m_State].iFrameStart < m_FrameMap[m_State].iFrameEnd)
			m_FrameMap[m_State].iFrameStart = m_FrameMap[m_State].iOriginStart;

		m_FrameMap[m_State].dwTime = GetTickCount64();
	}
}


void CWireman::PlayerPlaySound(TCHAR* _name)
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




int CWireman::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();


	return 0;
}

int CWireman::OutCollision(CObj* _target)
{
	OBJ_TYPE targetType = _target->Get_Type();


	return 0;
}

int CWireman::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();

	//m_vInfo.vPos += _dir;

	return 0;
}




