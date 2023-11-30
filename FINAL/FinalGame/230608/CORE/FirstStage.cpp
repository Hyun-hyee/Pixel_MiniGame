#include "stdafx.h"
#include "FirstStage.h"
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

CFirstStage::CFirstStage()
{
}

CFirstStage::~CFirstStage()
{
	Release();
}

void CFirstStage::Initialize()
{
	////배경 이미지 경로
	CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/testBack.jpg", L"FirstStage");
	//CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/Texture/Stage2bg_gray.bmp", L"FirstStage_gray");
	//CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/Texture/Stage2bg_slow.bmp", L"FirstStage_slow");
	CSceneManager::Get_Instance()->Set_BackSize({ 2145, 1732 });
	Set_BackGroundKey(L"FirstStage");

	////라인
	//CLineMgr::Get_Instance()->Add_Line({ -500,1208 }, {580,1208 });

	////벽
	//CSceneManager::Get_Instance()->AddLineRect(GRABWALL, 572, 856, 1200, 1244);
	//CSceneManager::Get_Instance()->AddLineRect(GRABWALL, 1192, 576, 2000, 1000);

	//BGM
	CSoundMgr::Get_Instance()->StopAll();
	//CSoundMgr::Get_Instance()->PlayBGM(L"song_killyourtv.ogg", SOUND_VOL1);
	//m_BGMkey = L"song_killyourtv.ogg";

	//캐릭터 생성
	//CObjMgr::Get_Instance()->Add_Object(PLAYER, CObjFactory<CPlayer>::Create());
	
	CObj* Temp = CObjFactory<CPlayer>::Create();
	Temp->SetPos(100.f, WINCY * 0.5f - 200);
	CObjMgr::Get_Instance()->Add_Object(OBJ_NONE, Temp);

}

void CFirstStage::Update()
{
	CObjMgr::Get_Instance()->Update();

}

void CFirstStage::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();

}
void CFirstStage::Render(HDC _hDC)
{
	BackGroundRender(_hDC);
	CObjMgr::Get_Instance()->Render(_hDC);
}

void CFirstStage::Release()
{
}




