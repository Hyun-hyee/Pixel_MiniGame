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
	CSoundMgr::Get_Instance()->PlayBGM(L"BubbleBobble_BGM.mp3", SOUND_VOL1);
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

	if (m_DownTime + 10000 < GetTickCount64() && !GameOver)
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
			CSoundMgr::Get_Instance()->PlayBGM(L"Bubble_Hurry.mp3", SOUND_VOL1);
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
}

void CPuzzleBobble::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();

}

void CPuzzleBobble::Render(HDC _hDC)
{
	BackGroundRender(_hDC);
	CObjMgr::Get_Instance()->Render(_hDC);
	//Rectangle(_hDC,0, MT + 520.f, WINCX, WINCY);

	//// 폰트 파일 경로 설정
	//const wchar_t* fontFilePath = L"../Resource/font/PF스타더스트 Bold.ttf";
	//// 사용할 폰트를 등록
	//fontCollection.AddFontFile(fontFilePath);

	//// 사용할 폰트 설정
	//Gdiplus::FontFamily fontFamily;
	//fontCollection.GetFamilies(1, &fontFamily, NULL);

	//// 폰트 크기 및 스타일 설정
	//Gdiplus::Font font(&fontFamily, 80, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	//// 텍스트 출력
	//Gdiplus::Graphics graphics(_hDC);

	//Gdiplus::PointF pointF(WINCX * 0.5f, WINCY * 0.5f);
	//Rectangle(_hDC,pointF.X, pointF.Y, pointF.X+10.f, pointF.Y+10.f);
	//const wchar_t* textToDisplay = L"SCORE : ";
	//Gdiplus::SolidBrush textBrush(Gdiplus::Color::Black);  
	//graphics.DrawString(textToDisplay, 10, &font, pointF, &textBrush);


}

void CPuzzleBobble::Release()
{
}




