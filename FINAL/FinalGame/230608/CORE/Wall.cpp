#include "stdafx.h"
#include "Wall.h"
#include "SceneManager.h"

CWall::CWall()
{
	m_Type = WALL;
}

CWall::~CWall()
{
	Release();
}

void CWall::Initialize(void)
{
	//RECT,Collide,FrontCollide 업데이트
	m_fAngle = 0.f;
}

void CWall::Update(void)
{
	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vInfo.vPos.x, m_vInfo.vPos.y, 0.f);

	m_vInfo.matWorld = matScale * matRotZ * matTrans;

	CObj::UpdatePoint();	
	__super::Update_Rect();
}

void CWall::LateUpdate(void)
{
}

void CWall::Render(HDC hDC)
{
		//CObj::CollideRender(hDC);
}

void CWall::Release(void)
{
}

void CWall::InitImage()
{
}

int CWall::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}

int CWall::OutCollision(CObj* _target)
{
	return 0;
}

int CWall::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}
