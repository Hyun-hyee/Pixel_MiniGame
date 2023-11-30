#include "stdafx.h"
#include "Tile.h"

#include <BmpMgr.h>

CTile::CTile()
{
}

CTile::~CTile()
{
}

void CTile::Initialize(void)
{
    m_tInfo.fCX = 32.f;
    m_tInfo.fCY = 32.f;


}

void CTile::Update(void)
{
    CObj::Update_Rect();
}

void CTile::LateUpdate(void)
{
}

void CTile::Render(HDC hDC)
{
    CObj::BasicRender(hDC);
}

void CTile::Release(void)
{

}

void CTile::InitImage()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_BLACK.bmp", L"BLACK");

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_DIAGONAL_LB.bmp", L"DIAGONAL_LB");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_DIAGONAL_LT.bmp", L"DIAGONAL_LT");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_DIAGONAL_RB.bmp", L"DIAGONAL_RB");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_DIAGONAL_RT.bmp", L"DIAGONAL_RT");

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_DIAGONAL_LB.bmp", L"EDGE_LB");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_DIAGONAL_LT.bmp", L"EDGE_LT");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_DIAGONAL_RB.bmp", L"EDGE_RB");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_DIAGONAL_RT.bmp", L"EDGE_RT");

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_DIAGONAL_LB.bmp", L"FLAT_BOTTOM");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_DIAGONAL_LT.bmp", L"FLAT_LEFT");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_DIAGONAL_RB.bmp", L"FLAT_RIGHT");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/WireMan_Resource/Image/Tile/_DIAGONAL_RT.bmp", L"FLAT_TOP");


}

int CTile::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
    return 0;
}

int CTile::OutCollision(CObj* _target)
{
    return 0;
}

int CTile::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
    return 0;
}

void CTile::Set_TileProperties(TILETYPE _TileType, TILEDIRECTION _TileDir)
{
    m_eTileType = _TileType;
    m_eTileDir = _TileDir;

    wstring wstr;

    switch (m_eTileType)
    {
    case TILETYPE::BLACK:
        wstr = L"BLACK";
            break;

    case TILETYPE::DIAGONAL:
        wstr = L"DIAGONAL";
        break;

    case TILETYPE::EDGE:
        wstr = L"EDGE";
        break;

    case TILETYPE::FLAT:
        wstr = L"FLAT";
        break;

    }

    switch (m_eTileDir)
    {
    case TILEDIRECTION::NONE:
        break;

    case TILEDIRECTION::LEFT:
        wstr += L"_LEFT";
            break;

    case TILEDIRECTION::TOP:
        wstr += L"_TOP";
        break;

    case TILEDIRECTION::RIGHT:
        wstr += L"_RIGHT";
        break;

    case TILEDIRECTION::BOTTOM:
        wstr += L"_BOTTOM";
        break;

    case TILEDIRECTION::LB:
        wstr += L"_LB";
        break;

    case TILEDIRECTION::RB:
        wstr += L"_RB";
        break;

    case TILEDIRECTION::LT:
        wstr += L"_LT";
        break;

    case TILEDIRECTION::RT:
        wstr += L"_RT";
        break;

    }

    wstr += L".bmp";
    m_OneImgKey = (TCHAR*)wstr.c_str();
}
