#include "stdafx.h"
#include "UIMgr.h"
#include "BmpMgr.h"
#include "SceneManager.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
	
}

CUIMgr::~CUIMgr()
{
}



void CUIMgr::Render(HDC hDC)
{
	UIRender(L"GameUI", hDC);
}

void CUIMgr::Release()
{
}




void CUIMgr::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/GameMachine.png", L"GameUI");

	//마우스 이미지 경로
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/images/effect/cursor.bmp", L"MOUSE");

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/HUD.png", L"TOP_UI");
	//UI TempUI = { L"TOP_UI" , 0, 0, WINCX, 36, true };
	//m_CheckUIList.insert({ L"TOP_UI" ,TempUI });

}

/******************************************************************************/
void CUIMgr::MouseRender(HDC hDC)
{
	//사용할 이미지 Key 가져오기
	Gdiplus::Bitmap* pImage = CBmpMgr::Get_Instance()->Find_Img(L"MOUSE");
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);	// 마우스 위치 값을 얻어오는 함수

	ScreenToClient(g_hWnd, &ptMouse); // 스크린 상의 좌표를 우리가 생성한 창 좌표로 변환

	Gdiplus::Graphics g(hDC);

	Gdiplus::ImageAttributes attr;
	attr.SetColorKey(Gdiplus::Color(255, 0, 255), Gdiplus::Color(255, 0, 255),
		Gdiplus::ColorAdjustTypeBitmap);

	g.DrawImage(pImage,
		Gdiplus::Rect(
			ptMouse.x - 25 * SMALL,
			ptMouse.y - 25 * SMALL,
			50 * SMALL, //복사 사이즈
			50 * SMALL //복사 사이즈
		),
		0,
		0,
		50,
		50, //이미지 원본 사이즈
		Gdiplus::UnitPixel, &attr);
}

void CUIMgr::UIRender(TCHAR* _key, HDC hDC)
{
	//사용할 이미지 Key 가져오기
	Gdiplus::Bitmap* Image = CBmpMgr::Get_Instance()->Find_Img(_key);
	//카메라 위치(디폴트 -> 플레이어)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	Gdiplus::Graphics g(hDC);

	//이미지 출력 (빠름, 알파블랜딩 X)
	Gdiplus::CachedBitmap cBitMap(Image, &g);
	g.DrawCachedBitmap(&cBitMap,
		0, // 복사 받을 위치 X,Y 좌표
		0
	);
	
}

