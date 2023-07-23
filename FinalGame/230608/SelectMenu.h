#pragma once
#include "Scene.h"
class CSelectMenu :
    public CScene
{
public:
	CSelectMenu();
	virtual ~CSelectMenu();

public:
	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render(HDC _hDC);
	void		Release();

private:
	int			SelectNum;


};

