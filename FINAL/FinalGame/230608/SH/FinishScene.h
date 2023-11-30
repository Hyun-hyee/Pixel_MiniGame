#pragma once
#include "Scene.h"
class CFinishScene :
	public CScene
{
public:
	CFinishScene();
	virtual ~CFinishScene();

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

