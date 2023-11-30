#pragma once
#include "Scene.h"

class CObj;

class CPuzzleBobble :
    public CScene
{
public:
	CPuzzleBobble();
	virtual ~CPuzzleBobble();

public:
	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render(HDC _hDC);
	void		Release();

private:
	DWORD		m_DownTime;
	CObj*		DownWall;

	bool		bHurry;

};

