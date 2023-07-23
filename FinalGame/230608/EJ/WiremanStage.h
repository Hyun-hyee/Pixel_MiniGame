#pragma once
#include "Scene.h"

class CBrick;
class CObj;

class CWiremanStage :
    public CScene
{
public:
    CWiremanStage();
    virtual ~CWiremanStage();

    // CScene을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hDC) override;
    virtual void Release() override;

    void Create_Bricks(UINT _iXBricks, UINT _iYBricks);

    void Plus_Score() {m_iScore +=100; }
    void Minus_Miss() { --m_iMiss; }

    void Delete_Brick(CBrick* _pBrick);

private:
    int m_iScore;
    int m_iMiss;

    vector<CBrick*> m_vecBricks;

    bool m_bClear;

    int m_iClearScore;
};

