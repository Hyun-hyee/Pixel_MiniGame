#include "stdafx.h"
#include "SkiingJumpingBoard.h"
#include "SceneManager.h"
#include "BmpMgr.h"

CSkiingJumpingBoard::CSkiingJumpingBoard()
{
	m_Type = SKIING_JUMPING_BOARD;
}

CSkiingJumpingBoard::~CSkiingJumpingBoard()
{
	Release();
}

void CSkiingJumpingBoard::Initialize(void)
{
	//RECT,Collide,FrontCollide 업데이트

	m_vPoint.push_back({ -40.f,-15.f,0.f });
	m_vPoint.push_back({ 40.f,-15.f,0.f });
	m_vPoint.push_back({ 40.f,20.f,0.f });
	m_vPoint.push_back({ -40.f,20.f,0.f });

	m_State = IDLE;

	for (auto& iter : m_vPoint)
	{
		m_vOriginPoint.push_back(iter);
	}

	m_fAngle = 0.f;

	InitImage();
}

void CSkiingJumpingBoard::Update(void)
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

void CSkiingJumpingBoard::LateUpdate(void)
{
}

void CSkiingJumpingBoard::Render(HDC hDC)
{
	CObj::CollideRender(hDC);
	CObj::FrameRender(hDC);
}

void CSkiingJumpingBoard::Release(void)
{

}

void CSkiingJumpingBoard::InitImage()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Images_Sh/cliff_tiled_0-sheet0.png", L"cliff");

	FRAME TempFrame;
	TempFrame.AnimKey = L"cliff";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 100;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 64.f;
	TempFrame.iFrameSizeY = 46.f;

	m_FrameMap.insert({ IDLE, TempFrame });
}

int CSkiingJumpingBoard::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}

int CSkiingJumpingBoard::OutCollision(CObj* _target)
{
	return 0;
}

int CSkiingJumpingBoard::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}
