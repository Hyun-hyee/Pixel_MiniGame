#include "stdafx.h"
#include "SceneManager.h"
#include "ObjMgr.h"
#include "Player.h"
#include "ObjFactory.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "UIMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "Wall.h"
#include "FirstStage.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;

bool g_SlowMotion = false;
bool g_CollideCheck = false;
DWORD g_SlowJumpTime = 0;

CSceneManager::CSceneManager()
{
	m_PlayScene = nullptr;
}

CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::Initialize()
{
	ShowCursor(FALSE);
	srand((unsigned int)time(NULL));

	ULONG_PTR ptr; //Gdi+����� ���� �����Ͱ�ü
	Gdiplus::GdiplusStartupInput in; //gdi+�Է°���ü
	Gdiplus::GdiplusStartup(&ptr, &in, 0); //����

	_hdc = GetDC(g_hWnd);
	::GetClientRect(g_hWnd, &_rect);

	_hdcBack = ::CreateCompatibleDC(_hdc); // _hdc�� ȣȯ�Ǵ� DC�� ����
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom); // _hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack); // DC�� BMP�� ����
	::DeleteObject(prev);

	//ObjMgr,MementoMgr (���� �߿�)
	CObjMgr::Get_Instance()->Initialize();

	//UIMgr
	CUIMgr::Get_Instance()->Initialize();

	//SoundMgr
	CSoundMgr::Get_Instance()->Initialize();
	
	//Scene ����
	SceneList.push_back(new CFirstStage);
	SceneList.back()->Initialize();
	SceneList.back()->Set_SceneOn(true);
	m_PlayScene = SceneList.back();

	//SceneList.push_back(new CFirstStage);
	//SceneList.back()->Set_SceneOn(false);

	//SceneList[0]->Set_NextScene(SceneList[1]);
	

	//SceneList[6]->Set_PrevScene(SceneList[5]);
	
}

void CSceneManager::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down('9'))
		ToPrevScene();

	else if (CKeyMgr::Get_Instance()->Key_Down('0'))
		ToNextScene();

	else if (CKeyMgr::Get_Instance()->Key_Down('C'))
		g_CollideCheck = !g_CollideCheck;

	for (auto iter = SceneList.begin(); iter != SceneList.end(); ++iter)
	{
		if ((*iter)->Get_SceneOn())
			(*iter)->Update();
	}
}

void CSceneManager::LateUpdate()
{
	for (auto iter = SceneList.begin(); iter != SceneList.end(); ++iter)
	{
		if ((*iter)->Get_SceneOn())
			(*iter)->LateUpdate();
   	}
	CKeyMgr::Get_Instance()->Key_LateUpdate();
}

void CSceneManager::Render()
{

	for (auto iter = SceneList.begin(); iter != SceneList.end(); ++iter)
	{
		if ((*iter)->Get_SceneOn())
			(*iter)->Render(_hdcBack);
	}

	if(g_CollideCheck)
		CLineMgr::Get_Instance()->Render(_hdcBack);

	CUIMgr::Get_Instance()->Render(_hdcBack);

	// Double Buffering
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY); // ��Ʈ �� : ��� ����
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}

void CSceneManager::ToNextScene()
{
	CScene* pNextScene = m_PlayScene->Get_NextScene();
	if (pNextScene)
	{		
		pNextScene->Set_SceneOn(true);
		m_PlayScene->Set_SceneOn(false);
		CObjMgr::Get_Instance()->Change_Scene();
		CLineMgr::Get_Instance()->Change_Scene();
		CObjMgr::Get_Instance()->Get_Player()->Initialize();

		pNextScene->Initialize();
		m_PlayScene = pNextScene;
	}
}

void CSceneManager::ToPrevScene()
{
	CScene* pPrevScene = m_PlayScene->Get_PrevScene();
	if (pPrevScene)
	{
		
		pPrevScene->Set_SceneOn(true);
		m_PlayScene->Set_SceneOn(false);
		CObjMgr::Get_Instance()->Change_Scene();
		CLineMgr::Get_Instance()->Change_Scene();
		CObjMgr::Get_Instance()->Get_Player()->Initialize();

		pPrevScene->Initialize();
		m_PlayScene = pPrevScene;
	}
}


void CSceneManager::ReplayBGM()
{
	m_PlayScene->ReplaySceneBGM();
}


void CSceneManager::AddLineRect(float _left, float _top, float _right, float _bottom)
{
	//CObjMgr::Get_Instance()->Add_Object(WALL, CObjFactory<CWall>::CreateRECT(_left, _top, _right, _bottom));

	CLineMgr::Get_Instance()->Add_Line({ _left -20.f,_top - 20.f }, { _right + 20.f,_top - 20.f });
}




void CSceneManager::Release()
{
	for (auto& iter : SceneList)
		Safe_Delete<CScene*>(iter);
	SceneList.clear();

	Gdiplus::GdiplusShutdown(ptr);
	CObjMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CUIMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
	//ReleaseDC(g_hWnd, m_hDC);
}

