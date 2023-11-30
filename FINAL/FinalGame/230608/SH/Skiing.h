#pragma once
#include "Scene.h"
class CSkiing :
	public CScene
{
public:
	CSkiing();
	virtual ~CSkiing();

public:
	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render(HDC _hDC);
	void		Release();

private:
	int iPosX;
	int iPosY;
};

