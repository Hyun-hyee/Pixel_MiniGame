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


void CScene::FontTextOut(HDC hDC, const wchar_t* _text, float _x, float _y)
{
	Gdiplus::Graphics graphics(hDC);

	// ����� �۲� ���� (�۲� �̸��� TrueType �۲� ���� ���ο� ���Ե� �̸�)
	Gdiplus::FontFamily fontFamily(L"Neo�ձٸ�");

	// �۲� ��ü ����
	Gdiplus::Font font(&fontFamily, 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

	// �۲��� ����Ͽ� �ؽ�Ʈ �׸���
	Gdiplus::SolidBrush brush(Gdiplus::Color::White); // �ؽ�Ʈ ���� (������)
	Gdiplus::PointF pointF(_x, _y); // �ؽ�Ʈ ���� ��ġ (x, y)

	//wchar_t text[] = L"SCORE : "; // �ؽ�Ʈ ����
	graphics.DrawString(_text, -1, &font, pointF, &brush);
}