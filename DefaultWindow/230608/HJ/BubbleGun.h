#pragma once
#include "Character.h"
class CBubbleGun :
    public CCharacter
{
public:
	CBubbleGun();
	virtual ~CBubbleGun();


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
	int					m_PrevBubble;
public:
	void				PlayerPlaySound(TCHAR* _name);
	void				ShootBubble();


private:
	CObj*		LastBubble;
public:
	void		SetLastBubble(CObj* _bubble) { LastBubble = _bubble; }
	void		ResetLastBubble() { LastBubble = nullptr; }
	CObj*		GetLastBubble() { return LastBubble; }
	bool		CheckLastBubble() { if (LastBubble != nullptr) return true; else return false; }
};

