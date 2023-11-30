#include "stdafx.h"
#include "FinishLine.h"
#include "SceneManager.h"
#include "BmpMgr.h"

CFinishLine::CFinishLine()
{
	m_Type = SKIING_FINISHLINE;
}

CFinishLine::~CFinishLine()
{
	Release();
}

void CFinishLine::Initialize(void)
{
	//RECT,Collide,FrontCollide 업데이트

	//m_vInfo.vPos = { WINCX / 2.f, WINCY / 2.f, 0.f };

	m_vPoint.push_back({ -450.f,0.f,0.f });
	m_vPoint.push_back({ 450.f,0.f,0.f });
	m_vPoint.push_back({ 450.f,66.f,0.f });
	m_vPoint.push_back({ -450.f,66.f,0.f });

	for (auto& iter : m_vPoint)
	{
		m_vOriginPoint.push_back(iter);
	}

	m_fAngle = 0.f;

	InitImage();
	m_State = IDLE;
}

void CFinishLine::Update(void)
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

void CFinishLine::LateUpdate(void)
{
}

void CFinishLine::Render(HDC hDC)
{
	//CObj::CollideRender(hDC);
	CObj::FrameRender(hDC);
	//CObj::BasicRender(hDC);
}

void CFinishLine::Release(void)
{

}

void CFinishLine::InitImage()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Images_Sh/FinishLine.bmp", L"FinishLine");

	FRAME TempFrame;
	TempFrame.AnimKey = L"FinishLine";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 100;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 900.f;
	TempFrame.iFrameSizeY = 66.f;

	m_FrameMap.insert({ IDLE, TempFrame });
}

int CFinishLine::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}

int CFinishLine::OutCollision(CObj* _target)
{
	return 0;
}

int CFinishLine::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}
