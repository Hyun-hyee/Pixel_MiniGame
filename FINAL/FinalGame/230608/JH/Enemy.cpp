#include "stdafx.h"
#include "Enemy.h"
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

CEnemy::CEnemy()
{
    m_Type = ENEMY;
	m_State = MOVE;
	m_bGuide = false;
	m_bMove = true;
	
}

CEnemy::~CEnemy()
{
}

void CEnemy::Initialize(void)
{
	m_vInfo.vLook = { 0.f,1.f,0.f };
	m_vInfo.vDir = m_vInfo.vLook;
	//originpoint로 다시 계산할 필요 없이 만들면 된다
	m_vPoint.push_back({ -25.f,25.f,0.f });
	m_vPoint.push_back({ 25.f,25.f,0.f });
	m_vPoint.push_back({ 25.f,-25.f,0.f });
	m_vPoint.push_back({ -25.f,-25.f,0.f });

	m_vPoint2.push_back({ 250.f,250.f,0.f });
	m_vPoint2.push_back({ 250.f,-250.f,0.f });
	m_vPoint2.push_back({ -250.f,-250.f,0.f });
	m_vPoint2.push_back({ -250.f,250.f,0.f });

	for (auto& iter : m_vPoint)
	{
		m_vOriginPoint.push_back(iter);
	}
	for (auto& iter : m_vPoint2)
	{
		m_vOriginPoint2.push_back(iter);
	}

	m_fAngle = 0.f;
	m_fAccel = 0.2f;
	m_fSpeed = 3.8f;

	m_Time = GetTickCount64();
	m_Move = GetTickCount64();
	m_MoveTime = 1500;
	m_AttackTime = 1000;
	InitImage();
}

void CEnemy::Update(void)
{
	StateUpdate();
	D3DXVec3TransformNormal(&m_vInfo.vDir, &m_vInfo.vLook, &m_vInfo.matWorld);
	if(m_State !=BOOM)
	m_vInfo.vPos += m_vInfo.vDir * m_fSpeed;
	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vInfo.vPos.x, m_vInfo.vPos.y, 0.f);

	m_vInfo.matWorld = matScale * matRotZ * matTrans;

	if (m_AttackTime + m_Time < GetTickCount64()&&m_bGuide)
	{
		CObj* Temp = CObjFactory<CBullet>::Create();
		Temp->SetOwner(this);
		Temp->SetPos(m_vInfo.vPos.x,m_vInfo.vPos.y);
		Temp->Set_Dir(m_vInfo.vDir);
		Temp->Set_Angle((m_fAngle+D3DXToRadian(180)));
		CObjMgr::Get_Instance()->Add_Object(BULLET, Temp);
		m_Time = GetTickCount64();
	}
	//vPos,vPoint,RECT,Collide,FrontCollide 업데이트
	if (m_MoveTime + m_Move < GetTickCount64()&&!m_bMove)
	{
		m_bMove = true;
	}
	if(m_bMove)
	Move();
	CObj::UpdatePoint();
	int i = 0;
	for (auto& iter : m_vPoint2)
	{
		iter = m_vOriginPoint2[i];

		D3DXVec3TransformCoord(&m_vPoint2[i], &m_vPoint2[i], &m_vInfo.matWorld);
		++i;
	}
	StateUpdate();
	CObj::Update_Rect();
	CObj::Move_Frame();
	D3DXVECTOR3 Nomal;
	float fa;
	if (CCollisionMgr::Get_Instance()->PolygonCollision(m_vPoint2, CObjMgr::Get_Instance()->Get_Tank()->GetPoint(), Nomal, fa))
	{
		m_bGuide = true;
	}
	else
	{
		m_bGuide = false;
	}

}

void CEnemy::LateUpdate(void)
{
}

void CEnemy::Render(HDC hDC)
{
	if (m_fFrontAngle == 0)
	{
		m_FrameMap[m_State].iMotion = 0;
	}
	else if (m_fFrontAngle == PI)
	{
		m_FrameMap[m_State].iMotion = 1;
	}
	//CObj::CollideRender(hDC);
	CObj::RotateFrameRender(hDC, D3DXToDegree(m_fAngle));
}

void CEnemy::Release(void)
{
}

void CEnemy::InitImage()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/JH/ENEMY.png", L"Enemy");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/JH/boom.png", L"boom");

	FRAME TempFrame;
	TempFrame.AnimKey = L"Enemy";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.iFrameSizeX = 60;
	TempFrame.iFrameSizeY = 50;

	m_FrameMap.insert({ MOVE, TempFrame });

	TempFrame.AnimKey = L"boom";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 9;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 100;
	TempFrame.iFrameSizeY = 100;
	
	m_FrameMap.insert({ BOOM, TempFrame });
}

int CEnemy::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();
	if (targetType == BULLET)
	{
		if (_target->GetOwner()->Get_Type() != ENEMY)
		{
				PlayerPlaySound(L"hitsound.wav");
				_target->Set_State(DEAD);
				m_State = BOOM;
			
		}
	}
	if (targetType == WALL)
	{
		if (!m_bGuide)
		{
			m_fAngle += D3DXToRadian(180.f);
			m_bMove = false;
		}
		else
			m_fSpeed *= -1;
	}
    return 0;
}

int CEnemy::OutCollision(CObj* _target)
{
	OBJ_TYPE targetType = _target->Get_Type();
	if (targetType == WALL)
	{
		if (m_bGuide)
			m_fSpeed *= -1;
	}
    return 0;
}

int CEnemy::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
    return 0;
}

void CEnemy::PlayerPlaySound(TCHAR* _name)
{
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_EFFECT2, SOUND_VOL2);
}

void CEnemy::StateUpdate()
{
	if (m_PrevState != m_State)
	{
		m_FrameMap[m_State].iFrameStart = 0;
		m_FrameMap[m_State].dwTime = GetTickCount64();
	}

	switch (m_State)
	{
	case BOOM:
		if (m_FrameMap[m_State].iFrameStart >= m_FrameMap[m_State].iFrameEnd)
			m_State = DEAD;
		break;
	}

	m_PrevState = m_State;

}

void CEnemy::Move()
{
	if (!m_bGuide)
	{
		if (m_MoveTime + m_Move < GetTickCount64())
		{
			int iRandom = rand() % 8;
			m_Move = GetTickCount64();
			m_fMove_Angle = iRandom * 45.f;
		}

		m_fAngle = D3DXToRadian(m_fMove_Angle);


	}
	else
	{
		m_vInfo.vDir = CObjMgr::Get_Instance()->Get_Tank()->Get_vInfo()->vPos - m_vInfo.vPos;
		//하 x ==0 y양수
		if (5 > m_vInfo.vDir.x && -5 < m_vInfo.vDir.x && 0 < m_vInfo.vDir.y)
		{
			m_fAngle = D3DXToRadian(0.f);
		}
		//상 x==0 y음수
		if (5 > m_vInfo.vDir.x && -5 < m_vInfo.vDir.x && 0 > m_vInfo.vDir.y)
		{
			m_fAngle = D3DXToRadian(180.f);
		}
		//좌  x음수 y==0
		if (0 > m_vInfo.vDir.x && 5 > m_vInfo.vDir.y && -5 < m_vInfo.vDir.y)
		{
			m_fAngle = D3DXToRadian(90.f);
		}
		//우 x양수 y==0
		if (0 < m_vInfo.vDir.x && 5 > m_vInfo.vDir.y && -5 < m_vInfo.vDir.y)
		{
			m_fAngle = D3DXToRadian(270.f);
		}
		//좌상 x 음수 y음수
		if (-5 > m_vInfo.vDir.x && -5 > m_vInfo.vDir.y)
		{
			m_fAngle = D3DXToRadian(135.f);
		}
		//우상 x양수 y양수
		if (5 < m_vInfo.vDir.x && 0 > m_vInfo.vDir.y)
		{
			m_fAngle = D3DXToRadian(225.f);
		}
		//좌하 x음수 y양수
		if (-5 > m_vInfo.vDir.x && 5 < m_vInfo.vDir.y)
		{
			m_fAngle = D3DXToRadian(45.f);
		}
		//우하 x양수 y양수
		if (0 < m_vInfo.vDir.x && 5 < m_vInfo.vDir.y)
		{
			m_fAngle = D3DXToRadian(315.f);
		}

	}
}
