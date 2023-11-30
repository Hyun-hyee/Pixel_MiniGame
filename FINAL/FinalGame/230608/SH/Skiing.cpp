#include "stdafx.h"
#include "Skiing.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "SkiingPlayer.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "Define.h"
#include "SceneManager.h"
#include "Wall.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "SkiingFlag.h"
#include "SkiingJumpingBoard.h"
#include "FinishLine.h"
#include "SkiingSnowman.h"

CSkiing::CSkiing()
{
}

CSkiing::~CSkiing()
{
	Release();
}

void CSkiing::Initialize()
{
	////배경 이미지 경로
	CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/Images_Sh/Skiing_BackGround.bmp", L"Skiing_BackGround");
	//CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/Texture/Stage2bg_gray.bmp", L"FirstStage_gray");
	//CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/Texture/Stage2bg_slow.bmp", L"FirstStage_slow");
	CSceneManager::Get_Instance()->Set_BackSize({ 1000, 13000 });
	Set_BackGroundKey(L"Skiing_BackGround");

	////라인
	//CLineMgr::Get_Instance()->Add_Line({ -500,1208 }, {580,1208 });

	////벽
	//CSceneManager::Get_Instance()->AddLineRect(GRABWALL, 572, 856, 1200, 1244);
	//CSceneManager::Get_Instance()->AddLineRect(GRABWALL, 1192, 576, 2000, 1000);

	//BGM
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"MainBgm.mp3", SOUND_VOL4);
	m_BGMkey = L"MainBgm.mp3";

	//캐릭터 생성
	//CObjMgr::Get_Instance()->Add_Object(PLAYER, CObjFactory<CPlayer>::Create());

	CObj* Temp = CObjFactory<CSkiingPlayer>::Create();
	Temp->SetPos(WINCX * 0.5f, 200.f);
	CObjMgr::Get_Instance()->Add_Object(SKIING_PLAYER, Temp);

	iPosY = 600;

	for (int i = 1; i <= 10; i++)
	{
		iPosX = 400;
		for (int j = 0; j < 2; j++)
		{
			CObjMgr::Get_Instance()->Add_Object(SKIING_FLAG, CObjFactory<CSkiingFlag>::Create(iPosX, iPosY));
			iPosX += 200;
			iPosY += 600;
		}
	}

	CObjMgr::Get_Instance()->Add_Object(SKIING_JUMPING_BOARD, CObjFactory<CSkiingJumpingBoard>::Create(400, 1500));
	CObjMgr::Get_Instance()->Add_Object(SKIING_JUMPING_BOARD, CObjFactory<CSkiingJumpingBoard>::Create(600, 3200));
	CObjMgr::Get_Instance()->Add_Object(SKIING_JUMPING_BOARD, CObjFactory<CSkiingJumpingBoard>::Create(400, 5000));
	CObjMgr::Get_Instance()->Add_Object(SKIING_JUMPING_BOARD, CObjFactory<CSkiingJumpingBoard>::Create(450, 6500));
	CObjMgr::Get_Instance()->Add_Object(SKIING_JUMPING_BOARD, CObjFactory<CSkiingJumpingBoard>::Create(550, 8500));
	CObjMgr::Get_Instance()->Add_Object(SKIING_JUMPING_BOARD, CObjFactory<CSkiingJumpingBoard>::Create(600, 11000));

	CObjMgr::Get_Instance()->Add_Object(SKIING_FINISHLINE, CObjFactory<CFinishLine>::Create(500, 13000));

	CObjMgr::Get_Instance()->Add_Object(SKIING_SNOWMAN, CObjFactory<CSkiingSnowman>::Create(500, 2000));
	CObjMgr::Get_Instance()->Add_Object(SKIING_SNOWMAN, CObjFactory<CSkiingSnowman>::Create(500, 4000));
	CObjMgr::Get_Instance()->Add_Object(SKIING_SNOWMAN, CObjFactory<CSkiingSnowman>::Create(500, 6000));
	CObjMgr::Get_Instance()->Add_Object(SKIING_SNOWMAN, CObjFactory<CSkiingSnowman>::Create(500, 7000));
	CObjMgr::Get_Instance()->Add_Object(SKIING_SNOWMAN, CObjFactory<CSkiingSnowman>::Create(500, 8000));
	CObjMgr::Get_Instance()->Add_Object(SKIING_SNOWMAN, CObjFactory<CSkiingSnowman>::Create(500, 10000));
}

void CSkiing::Update()
{

	if (dynamic_cast<CSkiingPlayer*>(CObjMgr::Get_Instance()->Get_ObjList(SKIING_PLAYER)->front())->GetFinish())
		CSceneManager::Get_Instance()->ToSelectScene(5);
	CObjMgr::Get_Instance()->Update();

}

void CSkiing::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();

}

void CSkiing::Render(HDC _hDC)
{
	BackGroundRender(_hDC);
	CObjMgr::Get_Instance()->Render(_hDC);
}

void CSkiing::Release()
{
}
