#include "stdafx.h"
#include "Scene.h"
#include "BmpMgr.h"
#include "SceneManager.h"
#include "SoundMgr.h"

void CScene::BackGroundRender(HDC hDC)
{
	//사용할 이미지 Key 가져오기
	Gdiplus::Bitmap* Image = CBmpMgr::Get_Instance()->Find_Img(m_BackGroundKey);
	//카메라 위치(디폴트 -> 플레이어)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	Gdiplus::Graphics g(hDC);

	//이미지 출력 (빠름, 알파블랜딩 X)
	Gdiplus::CachedBitmap cBitMap(Image, &g);
	g.DrawCachedBitmap(&cBitMap,
		ML - ((int)cameraPos.x - ML - MCX / 2), // 복사 받을 위치 X,Y 좌표
		MT - ((int)cameraPos.y - MT - MCY / 2)
	);
}

void CScene::BackGroundRender(HDC hDC, int _x, int _y, TCHAR* _BackKey)
{
	//사용할 이미지 Key 가져오기
	Gdiplus::Bitmap* Image = CBmpMgr::Get_Instance()->Find_Img(_BackKey);
	//카메라 위치(디폴트 -> 플레이어)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	Gdiplus::Graphics g(hDC);

	//이미지 출력 (빠름, 알파블랜딩 X)
	Gdiplus::CachedBitmap cBitMap(Image, &g);
	g.DrawCachedBitmap(&cBitMap,
		_x - ((int)cameraPos.x - WINCX / 2), // 복사 받을 위치 X,Y 좌표
		_y - ((int)cameraPos.y - WINCY / 2)
	);

}




void CScene::ReplaySceneBGM()
{
	CSoundMgr::Get_Instance()->StopAll();
	if(m_BGMkey != L"")
		CSoundMgr::Get_Instance()->PlayBGM(m_BGMkey, SOUND_VOL1);
}


void CScene::FontTextOut(HDC hDC, const wchar_t* _text, float _x, float _y)
{
	Gdiplus::Graphics graphics(hDC);

	// 사용할 글꼴 지정 (글꼴 이름은 TrueType 글꼴 파일 내부에 포함된 이름)
	Gdiplus::FontFamily fontFamily(L"Neo둥근모");

	// 글꼴 객체 생성
	Gdiplus::Font font(&fontFamily, 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

	// 글꼴을 사용하여 텍스트 그리기
	Gdiplus::SolidBrush brush(Gdiplus::Color::White); // 텍스트 색상 (검정색)
	Gdiplus::PointF pointF(_x, _y); // 텍스트 시작 위치 (x, y)

	//wchar_t text[] = L"SCORE : "; // 텍스트 내용
	graphics.DrawString(_text, -1, &font, pointF, &brush);
}