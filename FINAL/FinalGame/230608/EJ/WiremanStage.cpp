#include "stdafx.h"
#include "Define.h"
#include "WiremanStage.h"

#include "ObjFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "SceneManager.h"
#include <FontMgr.h>

#include "Wireman.h"
#include "Circle.h"
#include "Brick.h"


CWiremanStage::CWiremanStage() :
	m_iScore(NULL), m_iMiss(3), m_bClear(false), m_iClearScore(NULL)
{
}

CWiremanStage::~CWiremanStage()
{
	Release();
}

void CWiremanStage::Initialize()
{
	CObj* pTemp;

	//Background
	CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/Wireman_Resource/Image/_Background_Green.bmp", L"WM_BG_GREEN");
	CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/Wireman_Resource/Image/_Background_Orange.bmp", L"WM_BG_ORANGE");
	CSceneManager::Get_Instance()->Set_BackSize({ 910.f, 710.f });
	Set_BackGroundKey(L"WM_BG_ORANGE");

	//BGM
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"Ostrich_BGM.wav", SOUND_VOL4);

	//Player
	pTemp = CObjFactory<CWireman>::Create();
	CObjMgr::Get_Instance()->Add_Object(PLAYER, pTemp);

	//Bricks
	Create_Bricks(26, 5);

	//Circle
	pTemp = CObjFactory<CCircle>::Create(ML + MCX * 0.5f, MT + MCY * 0.5f, 32.f, 32.f);
	CObjMgr::Get_Instance()->Add_Object(CIRCLE, pTemp);

	//Camera
	CSceneManager::Get_Instance()->SetCameraPos({ ML + MCX * 0.5f, MT + MCY * 0.5f });

	//0724 오전 추가
	//게임 플레이 관련 수치 초기화. 
	m_bClear = false;		//클리어 여부
	m_iClearScore = 3000; //클리어 점수 조건
	m_iScore = 0;		//초기 점수
	m_iMiss = 3; //남은 목숨
}

void CWiremanStage::Update()
{
	CObjMgr::Get_Instance()->Update();

	if (m_bClear == true)
		if (!CObjMgr::Get_Instance()->Get_ObjList(CIRCLE)->empty())
		{
			CObjMgr::Get_Instance()->Get_ObjList(CIRCLE)->back()->Set_State(DEAD);
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlaySoundW(L"key_pick_up_01.wav", SOUND_PLAYER, SOUND_VOL3);
		}


	//공 아래로 빠짐
	if (0 == CObjMgr::Get_Instance()->Get_ObjList(CIRCLE)->size() && !m_bClear)
	{
		Minus_Miss();

		if (m_iMiss < 0)
			//게임 오버
			//재시작

			m_iScore -= 1000;

		CObj* pTemp = CObjFactory<CCircle>::Create(ML + MCX * 0.5f, MT + MCY * 0.5f, 32.f, 32.f);
		CObjMgr::Get_Instance()->Add_Object(CIRCLE, pTemp);
	}

	//if (m_vecBricks.empty())
	//{
	//	Create_Bricks(26, 4);
	//}
}

void CWiremanStage::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CWiremanStage::Render(HDC _hDC)
{
	BackGroundRender(_hDC);

	CObjMgr::Get_Instance()->Render(_hDC);

	wstring wstr = L"Ball : " + to_wstring(m_iMiss);
	CFontMgr::Get_Instance()->Draw_MyFont(_hDC, ML + 50, MB - 20, 50, 20, wstr);

	//0724 오전 수정
	wstr = L"Score : " + to_wstring(m_iScore) + L" / " + to_wstring(m_iClearScore);
	CFontMgr::Get_Instance()->Draw_MyFont(_hDC, MR - 100, MB - 20, 50, 20, wstr);

	if (m_bClear)
	{
		CFontMgr::Get_Instance()->Draw_MyBigFont(_hDC, ML + MCX * 0.5f, MT + MCY * 0.5f, 300, 50, L"CLEAR");

		//0724 오전 추가
		CFontMgr::Get_Instance()->Draw_MyFont(_hDC, ML + MCX * 0.5f, MT + MCY * 0.6f, 300, 50, L"Press Backspace back to Menu");

	}

}

void CWiremanStage::Release()
{
}

void CWiremanStage::Create_Bricks(UINT _iXBricks, UINT _iYBricks)
{
	//Bricks
	for (int i = 0; i < _iXBricks; ++i)
	{
		for (int j = 0; j < _iYBricks; ++j)
		{
			float fX = ML + 18.f + (32.f * i);
			float fY = MT + 18.f + (32.f * j);
			CObj* pTemp = CObjFactory<CBrick>::Create(fX, fY, 32.f, 32.f);
			dynamic_cast<CBrick*>(pTemp)->Set_Stage(this);
			CObjMgr::Get_Instance()->Add_Object(BRICK, pTemp);
			m_vecBricks.push_back(dynamic_cast<CBrick*>(pTemp));
		}
	}

}

void CWiremanStage::Delete_Brick(CBrick* _pBrick)
{
	for (auto iter = m_vecBricks.begin(); iter != m_vecBricks.end();)
	{
		if (_pBrick == *iter)
		{
			iter = m_vecBricks.erase(iter);

			Plus_Score();

			//클리어 조건
			if (m_iScore >= m_iClearScore)
				m_bClear = true;
		}
		else
			++iter;
	}
}
