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
	CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/puzzle_back.png", L"PuzzleBobble");
	CSceneManager::Get_Instance()->Set_BackSize({ 840, 640 });
	Set_BackGroundKey(L"PuzzleBobble");

	////벽
	//CSceneManager::Get_Instance()->AddLineRect(GRABWALL, 572, 856, 1200, 1244);
	//CSceneManager::Get_Instance()->AddLineRect(GRABWALL, 1192, 576, 2000, 1000);
	CObj* Temp = CObjFactory<CWall>::Create();
	Temp->SetPos(ML + 120.f,MT + 640 * 0.5f);
	Temp->AddPoint(-120.f, -640 * 0.5f);
	Temp->AddPoint(120.f, -640 * 0.5f);
	Temp->AddPoint(120.f, 640 * 0.5f);
	Temp->AddPoint(-120.f, 640 * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_NONE, Temp);
	
	Temp = CObjFactory<CWall>::Create();
	Temp->SetPos(ML + 420.f, MT + 35.f);
	Temp->AddPoint(-420.f, -35.f);
	Temp->AddPoint(420.f, -35.f);
	Temp->AddPoint(420.f, 35.f);
	Temp->AddPoint(-420.f, 35.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_NONE, Temp);

	Temp = CObjFactory<CWall>::Create();
	Temp->SetPos(ML + 720.f, MT + 640 * 0.5f);
	Temp->AddPoint(-120.f, -640 * 0.5f);
	Temp->AddPoint(120.f, -640 * 0.5f);
	Temp->AddPoint(120.f, 640 * 0.5f);
	Temp->AddPoint(-120.f, 640 * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_NONE, Temp);

	//BGM
	CSoundMgr::Get_Instance()->StopAll();
	//CSoundMgr::Get_Instance()->PlayBGM(L"song_killyourtv.ogg", SOUND_VOL1);
	//m_BGMkey = L"song_killyourtv.ogg";

	//캐릭터 생성
	Temp = CObjFactory<CBubbleGun>::Create();
	CObjMgr::Get_Instance()->Add_Object(PLAYER, Temp);

	CSceneManager::Get_Instance()->SetCameraPos({ ML + MCX * 0.5f, MT + MCY * 0.5f });

}

void CPuzzleBobble::Update()
{
	CObjMgr::Get_Instance()->Update();

}

void CPuzzleBobble::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();

}

void CPuzzleBobble::Render(HDC _hDC)
{
	BackGroundRender(_hDC);
	CObjMgr::Get_Instance()->Render(_hDC);
}

void CPuzzleBobble::Release()
{
}




