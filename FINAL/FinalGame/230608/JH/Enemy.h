#pragma once
#include "Character.h"
class CEnemy :
    public CCharacter
{
public:
	CEnemy();
	virtual ~CEnemy();

public:
	virtual void	Initialize(void)	override;
	virtual void		Update(void)	override;
	virtual void	LateUpdate(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;
	virtual void	InitImage()			override;

	virtual	int		InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)		override;
	virtual	int		OutCollision(CObj* _target)					override;
	virtual	int		OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)					override;
	void				PlayerPlaySound(TCHAR* _name);
private:
	void		StateUpdate();
	void		Move();

	//시간설정
	DWORD		m_AttackTime;
	DWORD		m_Time;
	DWORD		m_MoveTime;
	DWORD		m_Move;

	//시야충돌체
	vector <D3DXVECTOR3>		m_vPoint2;
	vector <D3DXVECTOR3>		m_vOriginPoint2;
	// 플레이어 추적
	bool		m_bGuide;
	float		m_fMove_Angle;
	bool		m_bMove;
	bool		m_bDead;
};

