#pragma once
#include "Obj.h"
class Component;

class CCharacter :
    public CObj
{
public:
	CCharacter();
	virtual ~CCharacter();

	virtual void Initialize()			override;
	virtual void Update()				override;
	virtual void LateUpdate(void)		override;
	virtual void Render(HDC hdc)		override;
	virtual void Release(void)			override;

public:
	virtual	int	 InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)	override;
	virtual	int	 OutCollision(CObj* _target)	override;
	virtual	int		OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)					override;
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

protected:
	vector<Component*>	_components;
	
protected:
	// ���� ����
	bool				m_bJump;
	float				m_fJump_Power;
	float				m_fJump_Angle;

	// �̴� ���� ����
	int					m_iAdditionJump_MaxCount;
	int					m_iAdditionJump_Count;

	bool				m_DirCheck[DIR_END];
public:
	//vector<Component*> 


protected:
	float			m_TimeStop_HurtCount;
	bool			m_TimeStop_HurtOn;
public:
	void			TimeStop_HurtCountUP() { m_TimeStop_HurtCount += 0.3f; }
	void			Set_TimeStop_HurtOn(bool _on) { m_TimeStop_HurtOn = _on; }

};

