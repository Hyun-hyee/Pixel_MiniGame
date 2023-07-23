#pragma once
#include "Obj.h"
class CFinishLine :
	public CObj
{
public:
	CFinishLine();
	virtual ~CFinishLine();

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

};

