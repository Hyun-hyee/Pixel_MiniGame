#include "stdafx.h"
#include "Tank.h"
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
#include "Bullet.h"
CTank::CTank()
{
	m_Type	  = TANK;
	m_bTop	  = true;
	m_bBottom = true;
	m_bLeft	  = true;
	m_bRight  = true;
	m_iCount = 0;
	m_iLife = 5;
	m_State = MOVE;
}

CTank::~CTank()
{
}

void CTank::Initialize(void)
{

	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);
	CCharacter::Initialize();

	m_vInfo.vPos  = { 700.f,3990.f,0.f};
	m_vInfo.vLook = { 0.f,-1.f,0.f };
	m_vInfo.vDir  = m_vInfo.vLook;

	//originpoint로 다시 계산할 필요 없이 만들면 된다
	m_vPoint.push_back({ -25.f,25.f,0.f });
	m_vPoint.push_back({ 25.f,25.f,0.f });
	m_vPoint.push_back({ 25.f,-25.f,0.f });
	m_vPoint.push_back({ -25.f,-25.f,0.f });

	for (auto& iter : m_vPoint)
	{
		m_vOriginPoint.push_back(iter);
	}
	m_GunPoint		 = { m_vInfo.vPos.x,m_vInfo.vPos.y-50.f,0.f };
	m_OriginGunPoint = m_GunPoint;

	m_fAngle		= 0.f;
	m_fAccel		= 0.2f;
	m_fSpeed		= 5.f;
	m_PlayerSoundCh = 0;

	InitImage();
}

void CTank::Update(void)
{
	CCharacter::Update();
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

void CTank::LateUpdate(void)
{
	if (m_iCount == 8 || m_iCount == -8)
	{
		m_fAngle = 0;
		m_iCount = 0;
	}
	if (m_iLife == 0)
	{
		m_iLife = 5;
	}
}

void CTank::Render(HDC hDC)
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
	CObj::RotateFrameRender(hDC, D3DXToDegree(m_fAngle));
}

void CTank::Release(void)
{
}

void CTank::InitImage()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/JH/player.png", L"Tank");

	FRAME TempFrame;
	TempFrame.AnimKey = L"Tank";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.iFrameSizeX = 60;
	TempFrame.iFrameSizeY = 50;

	m_FrameMap.insert({ MOVE, TempFrame });

}


void CTank::Key_Input(void)
{

	if (CKeyMgr::Get_Instance()->Key_Down('A') && m_bLeft)
	{
		m_fAngle -= D3DXToRadian(45.f);
		--m_iCount;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('D') && m_bRight)
	{
		m_fAngle += D3DXToRadian(45.f);
		++m_iCount;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing('W')&&m_bTop)
	{
		D3DXVec3TransformNormal(&m_vInfo.vDir, &m_vInfo.vLook, &m_vInfo.matWorld);
		m_vInfo.vPos += m_vInfo.vDir * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('S')&&m_bBottom)
	{
		D3DXVec3TransformNormal(&m_vInfo.vDir, &m_vInfo.vLook, &m_vInfo.matWorld);
		m_vInfo.vPos -= m_vInfo.vDir * m_fSpeed;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CObj* Temp = CObjFactory<CBullet>::Create();
		Temp->SetOwner(this);
		Temp->SetPos(m_vInfo.vPos.x, m_vInfo.vPos.y);
		Temp->Set_Dir(m_vInfo.vDir);
		CObjMgr::Get_Instance()->Add_Object(BULLET, Temp);
	}
}

void CTank::StateUpdate()
{
	//각 객체의 해당 애니메이션 키값 넣어주기
	if (m_PrevState != m_State)
	{
		m_FrameMap[m_State].iFrameStart = 0;
		m_FrameMap[m_State].dwTime = GetTickCount64();

	}

	switch (m_State)
	{

	}
}

void CTank::PlayerPlaySound(TCHAR* _name)
{
}

int CTank::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();
	if (targetType == WALL)
	{
		m_fSpeed *= -1;

	}
	if (targetType == BULLET)
	{
		if (_target->GetOwner() != this)
		{
			_target->Set_State(DEAD);
			--m_iLife;
		}
	}
	return 0;
}

int CTank::OutCollision(CObj* _target)
{
	m_bTop = true;
	m_bBottom = true;
	m_bLeft = true;
	m_bRight = true;
	OBJ_TYPE targetType = _target->Get_Type();
	if (targetType == WALL)
	{
		m_fSpeed *= -1;
	}
	return 0;
}

int CTank::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}