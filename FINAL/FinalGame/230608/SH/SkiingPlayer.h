#pragma once
#include "Character.h"
class CSkiingPlayer :
	public CCharacter
{
public:
	CSkiingPlayer();
	virtual ~CSkiingPlayer();


public:
	virtual void	Initialize(void)	override;
	virtual void		Update(void)	override;
	virtual void	LateUpdate(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;
	virtual void	InitImage()			override;

	virtual	int		InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)		override;
	virtual	int		OutCollision(CObj* _target)					override;
	virtual	int		OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)		override;
private:
	void		Key_Input(void);
	void		StateUpdate();

	int					m_PlayerSoundCh;
	D3DXVECTOR3			m_vPower;
	DWORD				m_dTime;
	DWORD				m_dStartTime;
	DWORD				m_dFinishTime;

	bool				m_bJumpEnd;
	bool				m_bGaugeOn;
	bool				m_bSound;
	int					m_iTime;
	int					m_iScore;
	int					m_iStartCount;

	float				m_fGauge;
	float				m_fPower;
	float				m_fJumpSizeX;
	float				m_fJumpSizeY;
	float				m_SkiingBreak;
	float				m_fSpeedPower;
	bool				Finish;
public:
	void				PlayerPlaySound(TCHAR* _name);
	bool				GetFinish() { return Finish; }
};

