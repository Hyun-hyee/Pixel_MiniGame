#pragma once
#include "Obj.h"

enum class TILETYPE
{
	NONE = 0, BLACK, DIAGONAL, EDGE, FLAT
};

enum class TILEDIRECTION
{
	NONE = 0, LEFT, TOP, RIGHT, BOTTOM, LT, RT, LB, RB
};

class CTile :
	public CObj
{
public:
	CTile();
	virtual ~CTile();

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

	void Set_TileProperties(TILETYPE _TileType, TILEDIRECTION _TileDir);

private:
	TILETYPE m_eTileType;
	TILEDIRECTION m_eTileDir;


};

