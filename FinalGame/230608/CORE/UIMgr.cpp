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

	//���콺 �̹��� ���
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/images/effect/cursor.bmp", L"MOUSE");

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Texture/HUD.png", L"TOP_UI");
	//UI TempUI = { L"TOP_UI" , 0, 0, WINCX, 36, true };
	//m_CheckUIList.insert({ L"TOP_UI" ,TempUI });

}

/******************************************************************************/
void CUIMgr::MouseRender(HDC hDC)
{
	//����� �̹��� Key ��������
	Gdiplus::Bitmap* pImage = CBmpMgr::Get_Instance()->Find_Img(L"MOUSE");
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);	// ���콺 ��ġ ���� ������ �Լ�

	ScreenToClient(g_hWnd, &ptMouse); // ��ũ�� ���� ��ǥ�� �츮�� ������ â ��ǥ�� ��ȯ

	Gdiplus::Graphics g(hDC);

	Gdiplus::ImageAttributes attr;
	attr.SetColorKey(Gdiplus::Color(255, 0, 255), Gdiplus::Color(255, 0, 255),
		Gdiplus::ColorAdjustTypeBitmap);

	g.DrawImage(pImage,
		Gdiplus::Rect(
			ptMouse.x - 25 * SMALL,
			ptMouse.y - 25 * SMALL,
			50 * SMALL, //���� ������
			50 * SMALL //���� ������
		),
		0,
		0,
		50,
		50, //�̹��� ���� ������
		Gdiplus::UnitPixel, &attr);
}

void CUIMgr::UIRender(TCHAR* _key, HDC hDC)
{
	//����� �̹��� Key ��������
	Gdiplus::Bitmap* Image = CBmpMgr::Get_Instance()->Find_Img(_key);
	//ī�޶� ��ġ(����Ʈ -> �÷��̾�)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	Gdiplus::Graphics g(hDC);

	//�̹��� ��� (����, ���ĺ��� X)
	Gdiplus::CachedBitmap cBitMap(Image, &g);
	g.DrawCachedBitmap(&cBitMap,
		0, // ���� ���� ��ġ X,Y ��ǥ
		0
	);
	
}

