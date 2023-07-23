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
#include "Bubble.h"

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
	m_vInfo.vPos = { ML + MCX / 2.f, MT +570.f, 0.f };
	m_vInfo.vLook = { 0.f,-1.f,0.f };
	m_vInfo.vDir = m_vInfo.vLook;

	m_vPoint.push_back({ -30.f,-30.f,0.f });
	m_vPoint.push_back({ 0.f,-60.f,0.f });
	m_vPoint.push_back({ 30.f,-30.f,0.f });
	m_vPoint.push_back({ 30.f,30.f,0.f });
	m_vPoint.push_back({ -30.f,30.f,0.f });

	for (auto& iter : m_vPoint)
	{
		m_vOriginPoint.push_back(iter);
	}

	m_fAngle = 0.f;
	m_fAccel = 0.2f;
	m_fSpeed = 7.f;
	m_PlayerSoundCh = 0;
	m_PrevBubble = 0;	
	LastBubble = nullptr;
	
	InitImage();
	CObj* Temp = CObjFactory<CBubble>::Create();
	Temp->Set_State(BUBBLE_RED);
	Temp->SetPos(m_vInfo.vPos.x, m_vInfo.vPos.y);
	Temp->SetMoveAngle(-m_fAngle + D3DX_PI / 2.f);
	CObjMgr::Get_Instance()->Add_Object(BUBBLE, Temp);

	Temp = CObjFactory<CBubble>::Create();
	Temp->Set_State(BUBBLE_RED);
	Temp->SetPos(m_vInfo.vPos.x, m_vInfo.vPos.y);
	Temp->SetMoveAngle(-m_fAngle + D3DX_PI / 2.f);
	CObjMgr::Get_Instance()->Add_Object(BUBBLE, Temp);

	Temp = CObjFactory<CBubble>::Create();
	Temp->Set_State(BUBBLE_RED);
	Temp->SetPos(m_vInfo.vPos.x - 80.f, m_vInfo.vPos.y + 20.f);
	Temp->SetMoveAngle(-m_fAngle + D3DX_PI / 2.f);
	CObjMgr::Get_Instance()->Add_Object(BUBBLE, Temp);
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
	CObj::RotateRender(hDC, D3DXToDegree(m_fAngle));
}

void CBubbleGun::Release(void)
{
}

void CBubbleGun::InitImage()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Arrow.bmp", L"ARROW");
	m_OneImgKey = L"ARROW";
}



void CBubbleGun::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		m_fAngle -= D3DXToRadian(3.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		m_fAngle += D3DXToRadian(3.f);



	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		ShootBubble();

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

void CBubbleGun::ShootBubble()
{
	if (!GameOver && !GameClear)
	{
		list<CObj*>::iterator iter = CObjMgr::Get_Instance()->Get_ObjList(BUBBLE)->end();
		iter--;
		iter--;
		CObj* Temp = *iter;
		Temp->SetPos(m_vInfo.vPos.x, m_vInfo.vPos.y);
		Temp->SetMoveAngle(-m_fAngle + D3DX_PI / 2.f);
		dynamic_cast<CBubble*>(Temp)->SetShoot(true);
		SetLastBubble(Temp);

		//대기
		m_PrevBubble = rand() % 5;
		iter++;
		(*iter)->SetPos(m_vInfo.vPos.x, m_vInfo.vPos.y);

		//대기
		m_PrevBubble = rand() % 5;
		Temp = CObjFactory<CBubble>::Create();

		if (m_PrevBubble == 0)
			Temp->Set_State(BUBBLE_RED);
		else if (m_PrevBubble == 1)
			Temp->Set_State(BUBBLE_GREEN);
		else if (m_PrevBubble == 2)
			Temp->Set_State(BUBBLE_BLUE);
		else if (m_PrevBubble == 3)
			Temp->Set_State(BUBBLE_YELLOW);
		else if (m_PrevBubble == 4)
			Temp->Set_State(BUBBLE_PURPLE);

		Temp->SetPos(m_vInfo.vPos.x - 80.f, m_vInfo.vPos.y + 20.f);
		CObjMgr::Get_Instance()->Add_Object(BUBBLE, Temp);
		PlayerPlaySound(L"Bubble_Shoot.wav");
	}


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




