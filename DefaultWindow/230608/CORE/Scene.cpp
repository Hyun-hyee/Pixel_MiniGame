#include "stdafx.h"
#include "Scene.h"
#include "BmpMgr.h"
#include "SceneManager.h"
#include "SoundMgr.h"

void CScene::BackGroundRender(HDC hDC)
{
	//����� �̹��� Key ��������
	Gdiplus::Bitmap* Image = CBmpMgr::Get_Instance()->Find_Img(m_BackGroundKey);
	//ī�޶� ��ġ(����Ʈ -> �÷��̾�)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	Gdiplus::Graphics g(hDC);

	//�̹��� ��� (����, ���ĺ��� X)
	Gdiplus::CachedBitmap cBitMap(Image, &g);
	g.DrawCachedBitmap(&cBitMap,
		ML - ((int)cameraPos.x - ML - MCX / 2), // ���� ���� ��ġ X,Y ��ǥ
		MT - ((int)cameraPos.y - MT - MCY / 2)
	);
}

void CScene::BackGroundRender(HDC hDC, int _x, int _y, TCHAR* _BackKey)
{
	//����� �̹��� Key ��������
	Gdiplus::Bitmap* Image = CBmpMgr::Get_Instance()->Find_Img(_BackKey);
	//ī�޶� ��ġ(����Ʈ -> �÷��̾�)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	Gdiplus::Graphics g(hDC);

	//�̹��� ��� (����, ���ĺ��� X)
	Gdiplus::CachedBitmap cBitMap(Image, &g);
	g.DrawCachedBitmap(&cBitMap,
		_x - ((int)cameraPos.x - WINCX / 2), // ���� ���� ��ġ X,Y ��ǥ
		_y - ((int)cameraPos.y - WINCY / 2)
	);

}




void CScene::ReplaySceneBGM()
{
	CSoundMgr::Get_Instance()->StopAll();
	if(m_BGMkey != L"")
		CSoundMgr::Get_Instance()->PlayBGM(m_BGMkey, SOUND_VOL1);
}


