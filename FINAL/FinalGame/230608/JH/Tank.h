#pragma once
#include "Character.h"
class CTank :
    public CCharacter
{
public:
	CTank();
	virtual ~CTank();

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
private:
	void		Key_Input(void);
	void		StateUpdate();

	int					m_PlayerSoundCh;

public:
	void				PlayerPlaySound(TCHAR* _name);
private:
	D3DXVECTOR3 m_GunPoint;
	D3DXVECTOR3 m_OriginGunPoint;
	bool		m_bTop;
	bool		m_bBottom;
	bool		m_bLeft;
	bool		m_bRight;
	float		m_fLength;
	int			m_iCount;
	int			m_iLife;
};

