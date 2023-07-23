#pragma once

#include "Define.h"
#include "Enum.h"
#include "Struct.h"
#include "Functor.h"

class CScene;
class CObj;

class CSceneManager
{
private:
	CSceneManager();
	~CSceneManager();

public:
	static CSceneManager* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CSceneManager;
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneManager* m_pInstance;


public:
	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render();
	void		Release();

private:
	HWND _hwnd = {};
	HDC _hdc = {};

private:
	// Double Buffering
	RECT _rect;
	HDC _hdcBack = {};
	HBITMAP _bmpBack = {};
	ULONG_PTR ptr; //Gdi+����� ���� �����Ͱ�ü

private:
	vector <CScene*> SceneList;
	CObj* m_pPlayer;


public:
	fPOINT GetCameraPos() { return _cameraPos; }
	void SetCameraPos(fPOINT pos) { _cameraPos = pos; }


private:
	fPOINT _cameraPos = { WINCX, WINCY };


public:
	void		ToNextScene();
	void		ToPrevScene();
	void		ToSelectScene(int _num);
	
private:
	CScene*		m_PlayScene;


private:
	fPOINT BackSize;
public:
	void Set_BackSize(fPOINT point) { BackSize.x = point.x; BackSize.y = point.y; }
	fPOINT Get_BackSize() { return BackSize; }
	void	ReplayBGM();

public:
	void AddLineRect(float _left, float _top, float _right, float _bottom);

};
