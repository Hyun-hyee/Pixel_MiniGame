#pragma once
#include "Obj.h"
class CBubble :
    public CObj
{
public:
	CBubble();
	virtual ~CBubble();

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
	bool			bMove;
	bool			bShoot;
	bool			bFall;
	bool			bTop;
	float			fDownDistance;

public:
	void			StateUpdate();
	
	void			SetShoot(bool _on) { bShoot = _on; }
	bool			GetShoot() { return bShoot; }

	void			SetFall(bool _on) { bFall = _on; }
	bool			GetFall() { return bFall; }

	void			SetTop(bool _on) { bTop = _on; }
	bool			GetTop() { return bTop; }

	void			SetMove(bool _on) { bMove = _on; }
	bool			GetMove() { return bMove; }

	void			MoveDown() { m_vInfo.vPos.y += fDownDistance; }


private:
	CObj* AdjacentBubbleList[6];

	static int					m_PlayerSoundCh;

public:
	void	FindPopBubble(vector<CObj*>& _popList, vector<CObj*> &_vistedList, OBJSTATE _color);
	void	FindTopBubble(bool &_TopCheck, vector<CObj*>& _vistedList);

	static vector<CObj*>		PopBubbleList;
	static vector<CObj*>		VisitedBubbleList;
	static	void				PopBubble();
	void						SetPopColor();
	void						ResetAdjacentList();
	CObj* GetAdjacentList(int i) { return AdjacentBubbleList[i]; }
	
	static void PlayerPlaySound(TCHAR* _name);
};

