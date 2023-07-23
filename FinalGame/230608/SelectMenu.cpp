#include "stdafx.h"
#include "SelectMenu.h"
#include "BmpMgr.h"
#include "SceneManager.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

CSelectMenu::CSelectMenu()
{
}

CSelectMenu::~CSelectMenu()
{
}

void CSelectMenu::Initialize()
{
	////배경 이미지 경로
	CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/Menu1.bmp", L"MENU_1");
	CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/Menu2.bmp", L"MENU_2");
	CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/Menu3.bmp", L"MENU_3");
	CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/Menu4.bmp", L"MENU_4");
	CSceneManager::Get_Instance()->Set_BackSize({ 840, 640 });
	Set_BackGroundKey(L"MENU_1");
	SelectNum = 1;

	CSceneManager::Get_Instance()->SetCameraPos({ ML + MCX * 0.5f, MT + MCY * 0.5f });


	//BGM
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"Menu.mp3", SOUND_VOL1);
}

void CSelectMenu::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down('S') || CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		++SelectNum;
		if (SelectNum >= 5)
			SelectNum = 1;

		if(SelectNum == 1)
			CSoundMgr::Get_Instance()->PlaySound(L"Select.wav", SOUND_EFFECT1, SOUND_VOL1);
		else if (SelectNum == 2)
			CSoundMgr::Get_Instance()->PlaySound(L"Select.wav", SOUND_EFFECT2, SOUND_VOL1);
		else if (SelectNum == 3)
			CSoundMgr::Get_Instance()->PlaySound(L"Select.wav", SOUND_EFFECT3, SOUND_VOL1);
		else if (SelectNum == 4)
			CSoundMgr::Get_Instance()->PlaySound(L"Select.wav", SOUND_EFFECT4, SOUND_VOL1);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('W') || CKeyMgr::Get_Instance()->Key_Down(VK_UP))
	{
		--SelectNum;
		if (SelectNum <= 0)
			SelectNum = 4;

		if (SelectNum == 1)
			CSoundMgr::Get_Instance()->PlaySound(L"Select.wav", SOUND_EFFECT1, SOUND_VOL1);
		else if (SelectNum == 2)
			CSoundMgr::Get_Instance()->PlaySound(L"Select.wav", SOUND_EFFECT2, SOUND_VOL1);
		else if (SelectNum == 3)
			CSoundMgr::Get_Instance()->PlaySound(L"Select.wav", SOUND_EFFECT3, SOUND_VOL1);
		else if (SelectNum == 4)
			CSoundMgr::Get_Instance()->PlaySound(L"Select.wav", SOUND_EFFECT4, SOUND_VOL1);
	}

	

	switch (SelectNum)
	{
	case 1:
		m_BackGroundKey = L"MENU_1";
		break;

	case 2:
		m_BackGroundKey = L"MENU_2";
		break;

	case 3:
		m_BackGroundKey = L"MENU_3";
		break;

	case 4:
		m_BackGroundKey = L"MENU_4";
		break;
	}
}

void CSelectMenu::LateUpdate()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE) || CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneManager::Get_Instance()->ToSelectScene(SelectNum);
	}
}

void CSelectMenu::Render(HDC _hDC)
{
	BackGroundRender(_hDC);
}

void CSelectMenu::Release()
{
}
