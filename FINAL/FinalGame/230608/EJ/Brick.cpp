#include "stdafx.h"
#include "Brick.h"
#include <BmpMgr.h>
#include "WiremanStage.h"
#include <random>


CBrick::CBrick() :
	m_pCurStage(nullptr)
{
	m_Type = BRICK;
}

CBrick::~CBrick()
{
}

void CBrick::Initialize(void)
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

	m_fAngle = 0.f;

	InitImage();
}

void CBrick::Update(void)
{
	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vInfo.vPos.x, m_vInfo.vPos.y, 0.f);

	m_vInfo.matWorld = matScale * matRotZ * matTrans;

	CObj::UpdatePoint();
	CObj::Update_Rect();

}

void CBrick::LateUpdate(void)
{
}

void CBrick::Render(HDC hDC)
{
	//Rectangle(hDC, m_tInfo.fX - m_tInfo.fCX * 0.5, m_tInfo.fY - m_tInfo.fCY * 0.5, m_tInfo.fX + m_tInfo.fCX * 0.5, m_tInfo.fY + m_tInfo.fCY * 0.5);

	//CObj::CollideRender(hDC);

	CObj::BasicRender(hDC);
}

void CBrick::Release(void)
{
}

void CBrick::InitImage()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Brick_1.bmp", L"BRICK_1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Brick_2.bmp", L"BRICK_2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Brick_3.bmp", L"BRICK_3");

	//0724 Ãß°¡
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/_Land_Effect_38x14.bmp", L"LAND_EFFECT");

	//Randomize
	random_device rd;
	mt19937_64 rng(rd());
	uniform_int_distribution<int> dis1to3(1, 3);

	UINT iRandom = dis1to3(rng);

	switch (iRandom)
	{
	default:
		m_OneImgKey = L"BRICK_1";
		break;

	case 1:
		m_OneImgKey = L"BRICK_1";
		break;

	case 2:
		m_OneImgKey = L"BRICK_2";
		break;

	case 3:
		m_OneImgKey = L"BRICK_3";
		break;
	}

	FRAME TempFrame;
	TempFrame.AnimKey = L"LAND_EFFECT";
	TempFrame.iFrameStart = 5;
	TempFrame.iOriginStart = 5;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 100;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 38;
	TempFrame.iFrameSizeY = 14;

	m_FrameMap.insert({ OBJ_STATE_END, TempFrame });
}

int CBrick::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();

	if (CIRCLE == targetType)
	{
		m_pCurStage->Delete_Brick(this);
		m_State = DEAD;
	}

	return 0;
}

int CBrick::OutCollision(CObj* _target)
{
	return 0;
}

int CBrick::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}
