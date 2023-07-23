#include "stdafx.h"
#include "Circle.h"
#include <BmpMgr.h>
#include <KeyMgr.h>
#include <SoundMgr.h>
#include "ObjMgr.h"

CCircle::CCircle() :
	m_bMove(false)
{
	m_Type = CIRCLE;
}

CCircle::~CCircle()
{
}

void CCircle::Initialize(void)
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_vPoint.push_back({ -16.f , -16.f, 0 });
	m_vPoint.push_back({ 16.f , -16.f, 0 });
	m_vPoint.push_back({ 16.f , 16.f, 0 });
	m_vPoint.push_back({ -16.f , 16.f, 0 });

	for (auto& iter : m_vPoint)
	{
		m_vOriginPoint.push_back(iter);
	}

	m_fAngle = D3DXToRadian(270);
	m_fSpeed = 10.f;

	m_vInfo.vLook = { -1.f,0.f,0.f };
	m_vInfo.vDir = { -1.f, 0.f , 0.f };

	InitImage();
}

void CCircle::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		CirclePlaySound(L"Fall_Effect.wav");
		m_bMove = true;
	}


	if (m_bMove)
	{
		Move();
		Reflection();
	}

	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vInfo.vPos.x, m_vInfo.vPos.y, 0.f);

	m_vInfo.matWorld = matScale * matRotZ * matTrans;

	CObj::UpdatePoint();
	CObj::Update_Rect();

}

void CCircle::LateUpdate(void)
{
}

void CCircle::Render(HDC hDC)
{
	//CObj::CollideRender(hDC);

	CObj::BasicRender(hDC);

	// Ellipse(hDC, m_tInfo.fX - m_tInfo.fCX * 0.5, m_tInfo.fY - m_tInfo.fCY * 0.5, m_tInfo.fX + m_tInfo.fCX * 0.5, m_tInfo.fY + m_tInfo.fCY * 0.5);
}

void CCircle::Release(void)
{
}

void CCircle::InitImage()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Ball.bmp", L"BALL");
	m_OneImgKey = L"BALL";
}

int CCircle::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();
	INFO targetInfo = *(_target->Get_Info());

	float fDegree = D3DXToDegree(m_fAngle);

	//공이 플레이어랑 닿았을 때
	if (PLAYER == targetType)
	{
		CirclePlaySound(L"TileLanding_Effect.wav");

		if (fDegree >= 180 && fDegree < 270)
			m_fAngle = D3DXToRadian(180 - (fDegree - 180));
		else if (fDegree >= 270 && fDegree < 180)
			m_fAngle = D3DXToRadian(90 - (fDegree - 270));
		else
		{
			if (m_tInfo.fX < CObjMgr::Get_Instance()->Get_Player()->Get_Info()->fX)
			{
				m_fAngle = D3DXToRadian(60);
			}
			else
				m_fAngle = D3DXToRadian(120);
		}
	}

	//공이 벽돌이랑 닿았을 때
	if (BRICK == targetType)
	{
		CirclePlaySound(L"TileLanding_Effect.wav");

		if (fDegree >= 0 && fDegree < 90)
		{
			if (targetInfo.fY > m_tInfo.fY) //위에서 충돌
				m_fAngle = D3DXToRadian(90 + (90 - fDegree));
			if(targetInfo.fX > m_tInfo.fX) //왼쪽에서 충돌
			m_fAngle = D3DXToRadian(360-fDegree);
		}
		else if (fDegree >= 90 && fDegree < 180)
		{
			if (targetInfo.fY > m_tInfo.fY) //위에서 충돌
				m_fAngle = D3DXToRadian(90 - ( fDegree-90));
			if (targetInfo.fX < m_tInfo.fX) //오른쪽에서 충돌
			m_fAngle = D3DXToRadian(180+(180-fDegree));
		}
		else if (fDegree >= 180 && fDegree < 270)
		{
			if (targetInfo.fY < m_tInfo.fY) //아래에서 충돌
				m_fAngle = D3DXToRadian(270+(270 - fDegree));
			if (targetInfo.fX < m_tInfo.fX) //오른쪽에서 충돌
			m_fAngle = D3DXToRadian(180-(fDegree-180));
		}
		else if (fDegree >= 270 && fDegree < 360)
		{
			if (targetInfo.fY < m_tInfo.fY) //아래에서 충돌
				m_fAngle = D3DXToRadian(270 - ( fDegree- 270 ));
			if (targetInfo.fX > m_tInfo.fX) //왼쪽에서 충돌
				m_fAngle = D3DXToRadian((360 - fDegree));
		}
	}

	return 0;
}

int CCircle::OutCollision(CObj* _target)
{
	OBJ_TYPE targetType = _target->Get_Type();

	return 0;
}

int CCircle::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();

	return 0;
}

void CCircle::Move()
{
	D3DXVec3TransformNormal(&m_vInfo.vDir, &m_vInfo.vLook, &m_vInfo.matWorld);
	m_vInfo.vPos += m_vInfo.vDir * m_fSpeed;

	float fDegree = D3DXToDegree(m_fAngle);

	//공이 위쪽 벽에 닿았을 때
	if (m_vInfo.vPos.y - 16.f < MT)
	{
		CirclePlaySound(L"TileLanding_Effect.wav");
		if (fDegree >= 0 && fDegree < 90)
			m_fAngle = D3DXToRadian(270 + (90 - fDegree));
		else if (fDegree >= 90 && fDegree < 180)
			m_fAngle = D3DXToRadian(270 - (fDegree - 90));
	}

	//공이 아래쪽 벽에 닿았을 때?
	if (m_vInfo.vPos.y + 16.f > MB)
	{
		CirclePlaySound(L"WireThrow_Effect.wav");
		m_State = DEAD;
	}

	//공이 왼쪽 벽에 닿았을 때
	if (m_vInfo.vPos.x - 16.f < ML)
	{
		CirclePlaySound(L"TileLanding_Effect.wav");
		if (fDegree >= 0 && fDegree < 90)
			m_fAngle = D3DXToRadian(90 + (90 - fDegree));
		else if (fDegree >= 270 && fDegree < 360)
			m_fAngle = D3DXToRadian(90 - (fDegree - 90));
	}

	//공이 오른쪽 벽에 닿았을 때
	if (m_vInfo.vPos.x + 16.f > MR)
	{
		CirclePlaySound(L"TileLanding_Effect.wav");
		if (fDegree >= 90 && fDegree < 180)
			m_fAngle = D3DXToRadian(90 - (fDegree - 90));
		else// if( fDegree >=180 && fDegree <270)
			m_fAngle = D3DXToRadian(270 + (270 - fDegree));
	}

}

void CCircle::Reflection()
{

}

void CCircle::CirclePlaySound(TCHAR* _name)
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

