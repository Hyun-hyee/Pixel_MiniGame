#pragma once
#include "Scene.h"
class CStartMenu :
    public CScene
{
public:
	CStartMenu();
	virtual ~CStartMenu();

public:
	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render(HDC _hDC);
	void		Release();

private:
	int			SelectNum;
};

