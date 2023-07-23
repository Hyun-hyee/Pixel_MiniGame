#pragma once
#include "Obj.h"
class CBullet :
    public CObj
{
public:
    CBullet();
    virtual ~CBullet();
public:

    // CObj을(를) 통해 상속됨
    virtual void Initialize(void) override;
    virtual void Update(void) override;
    virtual void LateUpdate(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void InitImage() override;
    virtual int InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle) override;
    virtual int OutCollision(CObj* _target) override;
    virtual int OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle) override;
private:
    bool m_bBullet;
    float m_fLength;

    DWORD		m_AttackTime;
    DWORD		m_Time;
};

