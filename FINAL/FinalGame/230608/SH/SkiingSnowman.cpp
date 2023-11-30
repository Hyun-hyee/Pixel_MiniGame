#include "stdafx.h"
#include "SkiingSnowman.h"
#include "SceneManager.h"
#include "BmpMgr.h"

CSkiingSnowman::CSkiingSnowman() : m_dTime(GetTickCount64())
{
	m_Type = SKIING_SNOWMAN;
}

CSkiingSnowman::~CSkiingSnowman()
{
	Release();
}

void CSkiingSnowman::Initialize(void)
{
	//RECT,Collide,FrontCollide 업데이트

	//m_vInfo.vPos = { WINCX / 2.f, WINCY / 2.f, 0.f };

	m_vInfo.vLook = { 1.f,0.f,0.f };
	m_vInfo.vDir = m_vInfo.vLook;

	m_vPoint.push_back({ -20.f,0.f,0.f });
	m_vPoint.push_back({ 20.f,0.f,0.f });
	m_vPoint.push_back({ 20.f,40.f,0.f });
	m_vPoint.push_back({ -20.f,40.f,0.f });

	for (auto& iter : m_vPoint)
	{
		m_vOriginPoint.push_back(iter);
	}

	m_fAngle = 0.f;

	m_fSpeed = 15.f;

	InitImage();
	m_State = IDLE;

	m_fPower.x = 1;
	m_fPower.y = 1;
}

void CSkiingSnowman::Update(void)
{
	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vInfo.vPos.x, m_vInfo.vPos.y, 0.f);

	m_vInfo.matWorld = matScale * matRotZ * matTrans;

	//속도
	m_fPower = m_vInfo.vDir * m_fSpeed;

	//반전
	if (MR - ML < m_vInfo.vPos.x)
	{
		if(m_vInfo.vDir.x == 1.f)
			m_vInfo.vDir.x = -1.f;
	}
	else if (ML + ML > m_vInfo.vPos.x)
	{
		if (m_vInfo.vDir.x == -1.f)
			m_vInfo.vDir.x = 1.f;
	}

	//MCX MCY ML MT
	//이동
	m_vInfo.vPos += m_fPower;

	CObj::UpdatePoint();
	__super::Update_Rect();
	CObj::Move_Frame();

}

void CSkiingSnowman::LateUpdate(void)
{
}

void CSkiingSnowman::Render(HDC hDC)
{
	//CObj::CollideRender(hDC);
	CObj::FrameRender(hDC);
	//CObj::BasicRender(hDC);
}

void CSkiingSnowman::Release(void)
{

}

void CSkiingSnowman::InitImage()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Images_Sh/yeti-sheet2.png", L"yeti-sheet2");

	FRAME TempFrame;
	TempFrame.AnimKey = L"yeti-sheet2";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 100;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 64.f;
	TempFrame.iFrameSizeY = 64.f;
	//64, 85
	m_FrameMap.insert({ IDLE, TempFrame });
}

int CSkiingSnowman::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();

	if (targetType == SKIING_PLAYER)
	{
		m_State = DEAD;
	}

	return 0;
}

int CSkiingSnowman::OutCollision(CObj* _target)
{
	return 0;
}

int CSkiingSnowman::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}
