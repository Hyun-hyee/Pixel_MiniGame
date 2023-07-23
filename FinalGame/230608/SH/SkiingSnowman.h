#pragma once
#include "Obj.h"
class CSkiingSnowman :
	public CObj
{
public:
	CSkiingSnowman();
	virtual ~CSkiingSnowman();

public:
	virtual void	Initialize(void)	override;
	virtual void		Update(void)		override;
	virtual void	LateUpdate(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;
	virtual void InitImage()			override;

public:
	virtual	int		InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)		override;
	virtual	int		OutCollision(CObj* _target)		override;
	virtual	int		OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)					override;

private:
	D3DXVECTOR3		m_fPower;
	DWORD			m_dTime;
};

