#include "stdafx.h"
#include "BubbleGun.h"
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


CBubbleGun::CBubbleGun()
{
	m_Type = PLAYER;
}

CBubbleGun::~CBubbleGun()
{
}


void CBubbleGun::Initialize(void)
{
	m_tInfo = { 200.f, 200.f, 200.f, 200.f };
	m_vInfo.vPos = { ML + MCX / 2.f, MT +610.f, 0.f };
	m_vInfo.vLook = { 0.f,-1.f,0.f };
	m_vInfo.vDir = m_vInfo.vLook;

	m_vPoint.push_back({ -100.f,-100.f,0.f });
	m_vPoint.push_back({ 100.f,-100.f,0.f });
	m_vPoint.push_back({ 150.f,0.f,0.f });
	m_vPoint.push_back({ 100.f,100.f,0.f });
	m_vPoint.push_back({ -100.f,100.f,0.f });

	for (auto& iter : m_vPoint)
	{
		m_vOriginPoint.push_back(iter);
	}

	m_fAngle = 0.f;
	m_fAccel = 0.2f;
	m_fSpeed = 7.f;
	m_PlayerSoundCh = 0;

	InitImage();
}

void CBubbleGun::Update(void)
{
	//키값 판단
	Key_Input();


	
		//상태 업데이트 (애니메이션 전환)
		StateUpdate();
	

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

void CBubbleGun::LateUpdate(void)
{
}

void CBubbleGun::Render(HDC hDC)
{
	if (m_fFrontAngle == 0)
	{
		m_FrameMap[m_State].iMotion = 0;
	}
	else if (m_fFrontAngle == PI)
	{
		m_FrameMap[m_State].iMotion = 1;
	}


	//if (g_CollideCheck)
	CObj::CollideRender(hDC);

}

void CBubbleGun::Release(void)
{
}

void CBubbleGun::InitImage()
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



void CBubbleGun::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		m_fAngle -= D3DXToRadian(3.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		m_fAngle += D3DXToRadian(3.f);

	/*if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
	{
		D3DXVec3TransformNormal(&m_vInfo.vDir, &m_vInfo.vLook, &m_vInfo.matWorld);
		m_vInfo.vPos += m_vInfo.vDir * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
	{
		D3DXVec3TransformNormal(&m_vInfo.vDir, &m_vInfo.vLook, &m_vInfo.matWorld);
		m_vInfo.vPos -= m_vInfo.vDir * m_fSpeed;
	}*/

}



/////////////////////////////////////////////////////////////////

//각 객체의 해당 애니메이션 키값 넣어주기
void CBubbleGun::StateUpdate()
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


void CBubbleGun::PlayerPlaySound(TCHAR* _name)
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




int CBubbleGun::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();


	return 0;
}

int CBubbleGun::OutCollision(CObj* _target)
{
	OBJ_TYPE targetType = _target->Get_Type();


	return 0;
}

int CBubbleGun::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();
	m_vInfo.vPos += _dir;
	return 0;
}




