#pragma once
#include "Scene.h"
class CTankWar :
    public CScene
{
public:
	CTankWar();
	virtual ~CTankWar();

public:
	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render(HDC _hDC);
	void		Release();
	void		Create_Wall();
private:
	bool m_bCreate1;
	bool m_bCreate2;
	bool m_bCreate3;
};

