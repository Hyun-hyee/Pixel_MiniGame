#include "stdafx.h"
#include "FinishScene.h"
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

CFinishScene::CFinishScene()
{
}

CFinishScene::~CFinishScene()
{
	Release();
}

void CFinishScene::Initialize()
{
	////배경 이미지 경로
	CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/Images_Sh/End.bmp", L"End");
	CSceneManager::Get_Instance()->Set_BackSize({ 1000, 700 });
	Set_BackGroundKey(L"End");

	//BGM
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"EndingSound.mp3", SOUND_VOL1);
	m_BGMkey = L"EndingSound.mp3";

	CSceneManager::Get_Instance()->SetCameraPos({ WINCX * 0.5f, 400 });

}

void CFinishScene::Update()
{
	CObjMgr::Get_Instance()->Update();

}

void CFinishScene::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();

}

void CFinishScene::Render(HDC _hDC)
{
	BackGroundRender(_hDC);
	CObjMgr::Get_Instance()->Render(_hDC);
}

void CFinishScene::Release()
{
}
