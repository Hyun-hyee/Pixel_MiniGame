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
	//RECT,Collide,FrontCollide ������Ʈ
	__super::Update_Rect();
}

void CWall::Update(void)
{
}

void CWall::LateUpdate(void)
{
}

void CWall::Render(HDC hDC)
{
	if (g_CollideCheck)
		CObj::CollideRender(hDC);
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
