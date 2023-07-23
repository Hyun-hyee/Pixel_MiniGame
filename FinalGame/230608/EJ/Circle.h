#pragma once
#include "Obj.h"
class CCircle :
    public CObj
{
public:
    CCircle();
    virtual ~CCircle();

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

    void CirclePlaySound(TCHAR* _name);
    void Move();
    void Reflection();
    
    int m_PlayerSoundCh = 0;
    bool m_bMove;
};

