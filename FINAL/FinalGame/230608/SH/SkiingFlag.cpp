#include "stdafx.h"
#include "SkiingFlag.h"
#include "SceneManager.h"
#include "BmpMgr.h"

CSkiingFlag::CSkiingFlag()
{
	m_Type = SKIING_FLAG;
}

CSkiingFlag::~CSkiingFlag()
{
	Release();
}

void CSkiingFlag::Initialize(void)
{
	//RECT,Collide,FrontCollide 업데이트

	//m_vInfo.vPos = { WINCX / 2.f, WINCY / 2.f, 0.f };

	m_vPoint.push_back({ -71.f,15.f,0.f });
	m_vPoint.push_back({ 71.f,15.f,0.f });
	m_vPoint.push_back({ 71.f,20.f,0.f });
	m_vPoint.push_back({ -71.f,20.f,0.f });

	for (auto& iter : m_vPoint)
	{
		m_vOriginPoint.push_back(iter);
	}

	m_fAngle = 0.f;

	InitImage();
	m_State = IDLE;
}

void CSkiingFlag::Update(void)
{
	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vInfo.vPos.x, m_vInfo.vPos.y, 0.f);

	m_vInfo.matWorld = matScale * matRotZ * matTrans;

	CObj::UpdatePoint();
	__super::Update_Rect();
	CObj::Move_Frame();

}

void CSkiingFlag::LateUpdate(void)
{
}

void CSkiingFlag::Render(HDC hDC)
{
	//CObj::CollideRender(hDC);
	CObj::FrameRender(hDC);
	//CObj::BasicRender(hDC);
}

void CSkiingFlag::Release(void)
{

}

void CSkiingFlag::InitImage()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Images_Sh/Flag.bmp", L"Flag");

	FRAME TempFrame;
	TempFrame.AnimKey = L"Flag";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 100;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 182.f;
	TempFrame.iFrameSizeY = 47.f;

	m_FrameMap.insert({ IDLE, TempFrame });
}

int CSkiingFlag::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}

int CSkiingFlag::OutCollision(CObj* _target)
{
	return 0;
}

int CSkiingFlag::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}
