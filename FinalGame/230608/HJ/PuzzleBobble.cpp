#include "stdafx.h"
#include "PuzzleBobble.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "Player.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "Define.h"
#include "SceneManager.h"
#include "Wall.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "BubbleGun.h"
#include "Bubble.h"

bool		GameOver = false;
bool		GameClear = false;
int			BubbleScore = 0;

CPuzzleBobble::CPuzzleBobble()
{
}

CPuzzleBobble::~CPuzzleBobble()
{
	Release();
}

void CPuzzleBobble::Initialize()
{
	////배경 이미지 경로
	CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/puzzle_back.bmp", L"PuzzleBobble");
	CSceneManager::Get_Instance()->Set_BackSize({ 840, 640 });
	Set_BackGroundKey(L"PuzzleBobble");

	////벽
	//CSceneManager::Get_Instance()->AddLineRect(GRABWALL, 572, 856, 1200, 1244);
	//CSceneManager::Get_Instance()->AddLineRect(GRABWALL, 1192, 576, 2000, 1000);

	CObj* Temp = CObjFactory<CWall>::Create();
	Temp->SetPos(ML + 420.f, MT + 35.f);
	Temp->AddPoint(-420.f, -35.f);
	Temp->AddPoint(420.f, -35.f);
	Temp->AddPoint(420.f, 35.f);
	Temp->AddPoint(-420.f, 35.f);
	DownWall = Temp;
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	
	Temp = CObjFactory<CWall>::Create();
	Temp->SetPos(ML + 120.f,MT + 640 * 0.5f);
	Temp->AddPoint(-120.f, -640 * 0.5f);
	Temp->AddPoint(120.f, -640 * 0.5f);
	Temp->AddPoint(120.f, 640 * 0.5f);
	Temp->AddPoint(-120.f, 640 * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	

	Temp = CObjFactory<CWall>::Create();
	Temp->SetPos(ML + 720.f, MT + 640 * 0.5f);
	Temp->AddPoint(-120.f, -640 * 0.5f);
	Temp->AddPoint(120.f, -640 * 0.5f);
	Temp->AddPoint(120.f, 640 * 0.5f);
	Temp->AddPoint(-120.f, 640 * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//BGM
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"BubbleBobble_BGM.mp3", SOUND_VOL3);
	m_BGMkey = L"BubbleBobble_BGM.mp3";

	//캐릭터 생성
	Temp = CObjFactory<CBubbleGun>::Create();
	CObjMgr::Get_Instance()->Add_Object(PLAYER, Temp);

	//Temp = CObjFactory<CBubble>::Create();
	//Temp->SetPos(ML + MCX*0.5f, MT + MCY * 0.5f);
	//CObjMgr::Get_Instance()->Add_Object(BUBBLE, Temp);

	m_DownTime = GetTickCount64();
	bHurry = false;
	CSceneManager::Get_Instance()->SetCameraPos({ ML + MCX * 0.5f, MT + MCY * 0.5f });

}

void CPuzzleBobble::Update()
{
	CObjMgr::Get_Instance()->Update();
	
	list<CObj*>* BubbleList = CObjMgr::Get_Instance()->Get_ObjList(BUBBLE);

	if (m_DownTime + 10000 < GetTickCount64() && !GameOver && !GameClear)
	{
		for (auto& iter : *BubbleList)
		{
			if(dynamic_cast<CBubble*>(iter)->GetShoot())
				dynamic_cast<CBubble*> (iter)->MoveDown();
			
		}
		DownWall->SetPos(DownWall->GetPosX(), DownWall->GetPosY() + 40.f);
		
		if (DownWall->GetPosY() >= MT + 250.f && !bHurry)
		{
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlayBGM(L"Bubble_Hurry.mp3", SOUND_VOL3);
			bHurry = true;
		}
		
		m_DownTime = GetTickCount64();
	}

	bool CheckGameOver = false;
	for (auto& iter : *BubbleList)
	{
		if (iter->GetPosY() >= MT + 520.f &&  !dynamic_cast<CBubble*>(iter)->GetMove() && !dynamic_cast<CBubble*>(iter)->GetFall())
			CheckGameOver = true;
	}
	
	if (CheckGameOver &&  !GameOver)
	{
		for (auto& iter : *BubbleList)
		{
			iter->Set_State(BUBBLE_GRAY);
		}
		CSoundMgr::Get_Instance()->StopAll();
		CSoundMgr::Get_Instance()->PlaySound(L"Bubble_GameOver.mp3", SOUND_GAMEOVER, SOUND_VOL3);
		GameOver = true;
	}


	if (CObjMgr::Get_Instance()->Get_ObjList(BUBBLE)->size() >= 3)
	{
		CObj* BubbleGun = CObjMgr::Get_Instance()->Get_Player();
		
		if (dynamic_cast<CBubbleGun*> (BubbleGun)->CheckLastBubble())
		{
 			CObj* Temp = dynamic_cast<CBubbleGun*> (BubbleGun)->GetLastBubble();
  			dynamic_cast<CBubble*> (Temp)->FindPopBubble(CBubble::PopBubbleList, CBubble::VisitedBubbleList, (Temp)->Get_State());
			 
			CBubble::PopBubble();
			CBubble::PopBubbleList.clear();
			CBubble::VisitedBubbleList.clear();
		}
	}

	if (BubbleScore >= 4000 && !GameClear)
	{
		GameClear = true;
		for (auto& iter : *BubbleList)
		{
			dynamic_cast<CBubble*>(iter)->SetPopColor();
		}
		CSoundMgr::Get_Instance()->StopAll();
		CSoundMgr::Get_Instance()->PlaySound(L"Bubble_Clear.wav", SOUND_GAMEOVER, SOUND_VOL3);
	}
}

void CPuzzleBobble::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();

}

void CPuzzleBobble::Render(HDC _hDC)
{
	BackGroundRender(_hDC);
	CObjMgr::Get_Instance()->Render(_hDC);

	wstring wcharValue = L"SCORE : "; 

	// int 값을 wchar_t 문자열로 변환
	std::wstring intValueStr = std::to_wstring(BubbleScore);

	// wchar_t 문자열과 wchar_t 변수를 합침
	intValueStr =  wcharValue + intValueStr;
	const wchar_t* str = intValueStr.c_str();

	//FontTextOut(_hDC, str, ML + 30.f, 100.f);
	FontTextOut(_hDC, str, WINCX*0.5f -80.f, 100.f);

	if(GameClear)
		FontTextOut(_hDC, L"*** STAGE CLEAR ***", WINCX * 0.5f - 130.f, 250.f);
	else if (GameOver)
		FontTextOut(_hDC, L"*** GAME OVER ***", WINCX * 0.5f - 120.f, 250.f);

}

void CPuzzleBobble::Release()
{
}




