#include "stdafx.h"
#include "TileMgr.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}

CTileMgr::~CTileMgr()
{
}

void CTileMgr::Initialize()
{
	if (!m_vecTIle.empty())
		return;


}

void CTileMgr::Update()
{
}

void CTileMgr::Late_Update()
{
}

void CTileMgr::Render(HDC hDC)
{
}

void CTileMgr::Release()
{
}

void CTileMgr::Change_Tile()
{
}

void CTileMgr::Save_Tile()
{
}

void CTileMgr::Load_Tile()
{
}
