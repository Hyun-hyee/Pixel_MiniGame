#include "stdafx.h"
#include "Bullet.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "SceneManager.h"
#include "BmpMgr.h"
#include "BitMap.h"
#include "CameraComponent.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "ObjFactory.h"
#include "CameraComponent.h"
#include "UIMgr.h"
#include "SoundMgr.h"
CBullet::CBullet()
{
    m_Type = BULLET;
    m_bBullet = true;
    m_State = MOVE;
}

CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
    m_vInfo.vLook = { 0.f,-1.f,0.f };
    m_vInfo.vDir = m_vInfo.vLook;
    m_vPoint.push_back({ -5.f,5.f,0.f });
    m_vPoint.push_back({ 5.f,5.f,0.f });
    m_vPoint.push_back({ 5.f,-5.f,0.f });
    m_vPoint.push_back({ -5.f,-5.f,0.f });

    for (auto& iter : m_vPoint)
    {
        m_vOriginPoint.push_back(iter);
    }

    m_fSpeed = 10.f;
    m_Time = GetTickCount64();
    m_AttackTime = 2000;

    InitImage();
}

void CBullet::Update(void)
{
    D3DXMATRIX	matScale, matRotZ, matTrans;

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, m_fAngle);
    D3DXMatrixTranslation(&matTrans, m_vInfo.vPos.x, m_vInfo.vPos.y, 0.f);

    m_vInfo.matWorld = matScale * matRotZ * matTrans;

    if (m_bBullet)
    {
     /*   m_vInfo.vDir = CObjMgr::Get_Instance()->Get_Tank()->Get_vInfo()->vDir;*/
        m_fLength = sqrtf(m_vInfo.vDir.x * m_vInfo.vDir.x + m_vInfo.vDir.y * m_vInfo.vDir.y);
        //m_fAngle = CObjMgr::Get_Instance()->Get_Tank()->Get_Angle();
        //m_bBullet = false;
        m_vInfo.vDir.x /= m_fLength;
        m_vInfo.vDir.y /= m_fLength;
        m_vInfo.vDir.z = 0.f;
        m_bBullet = false;
    }
    //float fAngle = D3DXToDegree(m_fAngle);
    //m_vInfo.vPos.x += cosf(fAngle+1) * m_fSpeed;
    //m_vInfo.vPos.y -= sinf(fAngle+1) * m_fSpeed;
    m_vInfo.vPos += m_vInfo.vDir * m_fSpeed;
    CObj::UpdatePoint();
    CObj::Update_Rect();
    CObj::Move_Frame();
}

void CBullet::LateUpdate(void)
{
    if (m_AttackTime + m_Time < GetTickCount64())
        m_State = DEAD;
}

void CBullet::Render(HDC hDC)
{
    //CObj::CollideRender(hDC);
    CObj::RotateFrameRender(hDC, D3DXToDegree(m_fAngle));
}

void CBullet::Release(void)
{

}

void CBullet::InitImage()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/JH/bullet.png", L"Bullet");

    FRAME TempFrame;
    TempFrame.AnimKey = L"Bullet";
    TempFrame.iFrameStart = 0;
    TempFrame.iFrameEnd = 0;
    TempFrame.iMotion = 0;
    TempFrame.iFrameSizeX = 20;
    TempFrame.iFrameSizeY = 40;

    m_FrameMap.insert({ MOVE, TempFrame });
}

int CBullet::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
    OBJ_TYPE targetType = _target->Get_Type();
    if (targetType == WALL)
    {
        m_State = DEAD;

    }
    return 0;
}

int CBullet::OutCollision(CObj* _target)
{
    return 0;
}

int CBullet::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
    return 0;
}
