#pragma once
#include "Obj.h"
#include "Character.h"

class CPlayer :
    public CCharacter
{
public:
	CPlayer();
	virtual ~CPlayer();
	

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

	void		Jump();

	void		StateUpdate();

private:
	bool				EDITMODE;
	bool				CAMERAMODE;

	int					m_PlayerSoundCh;
					
public:
	void				PlayerPlaySound(TCHAR* _name);
};

