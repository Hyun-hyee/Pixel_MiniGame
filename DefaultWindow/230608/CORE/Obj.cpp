#include "stdafx.h"
#include "Obj.h"
#include "BitMap.h"
#include "SceneManager.h"
#include "BmpMgr.h"

CObj::CObj() :
	m_fSpeed(0.f), m_State(OBJ_STATE_NONE), m_Type(OBJ_NONE),
	m_fAccel(0.f), m_Owner(nullptr),
	m_PrevState(OBJ_STATE_END),
	m_OneImgKey(L""), m_FrameReverse(false)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_vInfo, sizeof(m_vInfo));
	D3DXMatrixIdentity(&m_vInfo.matWorld);
}

CObj::~CObj()
{
}

void CObj::Render(HDC hDC)
{
}

void CObj::Update_Rect()
{
	m_tInfo.fX = m_vInfo.vPos.x;
	m_tInfo.fY = m_vInfo.vPos.y;
}

void CObj::UpdatePoint()
{
	int i = 0;
	for (auto& iter : m_vPoint)
	{
		iter = m_vOriginPoint[i];

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_vInfo.matWorld);
		++i;
	}
}

void CObj::CollideRender(HDC hDC)
{
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	HPEN myPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	MoveToEx(hDC, (int)m_vPoint[0].x - ((int)cameraPos.x - ML - MCX / 2), (int)m_vPoint[0].y - ((int)cameraPos.y - MT - MCY / 2), nullptr);

	for (int i = 0; i < m_vPoint.size(); ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x - ((int)cameraPos.x - ML - MCX / 2), (int)m_vPoint[i].y - ((int)cameraPos.y - MT - MCY / 2));

		if (i > 0)
			continue;

		/*Ellipse(hDC,
			int(m_vPoint[i].x - 5.f),
			int(m_vPoint[i].y - 5.f),
			int(m_vPoint[i].x + 5.f),
			int(m_vPoint[i].y + 5.f));*/
	}

	LineTo(hDC, (int)m_vPoint[0].x - ((int)cameraPos.x - ML - MCX / 2), (int)m_vPoint[0].y - ((int)cameraPos.y - MT - MCY / 2));


	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	SelectObject(hDC, oldPen);
	DeleteObject(myPen);
}

void CObj::CollideRender(HDC hDC, RECT _collide)
{
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	HPEN myPen = CreatePen(PS_SOLID, 0, RGB(255, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	Rectangle(hDC, _collide.left - ((float)cameraPos.x - (ML + MCX / 2)),
		_collide.top - ((float)cameraPos.y - (MT + MCY / 2)),
		_collide.right - ((float)cameraPos.x - (ML + MCX / 2)),
		_collide.bottom - ((float)cameraPos.y - (MT + MCY / 2)));

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	SelectObject(hDC, oldPen);
	DeleteObject(myPen);

}


void CObj::RatioFixByImage(const TCHAR* _tcAnimKey)
{
	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(m_FrameMap[m_State].AnimKey);
	m_tInfo.fRatioX = m_tInfo.fCX / (float)pBitMap->Get_Image()->GetWidth();
	m_tInfo.fRatioY = m_tInfo.fCY / (float)pBitMap->Get_Image()->GetHeight();
}

void CObj::BasicRender(HDC hDC)
{
	//카메라 위치(디폴트 -> 플레이어)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(m_OneImgKey);

	Gdiplus::Bitmap* pImage;

	//사용할 이미지 Key 가져오기
	pImage = pBitMap->Get_Image();



	Gdiplus::Graphics g(hDC);

	//이미지 출력 (빠름, 알파블랜딩 X)
	g.DrawImage(pImage,
		Gdiplus::Rect(
			((int)(m_tInfo.fX - m_tInfo.fCX * 0.5f) - ((int)cameraPos.x - (ML + MCX / 2))),
			((int)(m_tInfo.fY - m_tInfo.fCY * 0.5f) - ((int)cameraPos.y - (MT + MCY / 2))),
			m_tInfo.fCX,  //복사 사이즈
			m_tInfo.fCY //복사 사이즈
		),
		0,
		0,
		pImage->GetWidth(),
		pImage->GetHeight(), //이미지 원본 사이즈
		Gdiplus::UnitPixel);


}

void CObj::FrameRender(HDC hDC)
{
	//TCHAR* temp = CBmpMgr::Get_Instance()->Add_TCHAR_wstring(m_FrameMap[m_State].AnimKey, L"_M1");
	// 사용할 CBitmap
	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(m_FrameMap[m_State].AnimKey);
	Gdiplus::Bitmap* pImage;

	//사용할 이미지 Key 가져오기
	pImage = pBitMap->Get_Image();

	//카메라 위치(디폴트 -> 플레이어)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	// 캔버스
	Gdiplus::Graphics g(hDC);


	Gdiplus::ImageAttributes attr;

	if (m_fFrontAngle == 0 || (m_FrameReverse == true && m_fFrontAngle == PI))
	{
		g.DrawImage(pImage,
			Gdiplus::Rect(
				((int)(m_tInfo.fX - m_tInfo.fCX * 0.5f) - ((int)cameraPos.x - (ML + MCX / 2))),
				((int)(m_tInfo.fY - m_tInfo.fCY * 0.5f) - ((int)cameraPos.y - (MT + MCY / 2))),
				(int)m_FrameMap[m_State].iFrameSizeX, //복사 사이즈
				(int)m_FrameMap[m_State].iFrameSizeY  //복사 사이즈
			),
			m_FrameMap[m_State].iFrameStart * (int)m_FrameMap[m_State].iFrameSizeX,
			m_FrameMap[m_State].iMotion * (int)m_FrameMap[m_State].iFrameSizeY,
			(int)m_FrameMap[m_State].iFrameSizeX,
			(int)m_FrameMap[m_State].iFrameSizeY, //이미지 원본 사이즈
			Gdiplus::UnitPixel, &attr);
	}
	else if (m_fFrontAngle == PI || (m_FrameReverse == true && m_fFrontAngle == 0))
	{
		g.DrawImage(pImage,
			Gdiplus::Rect(
				((int)(m_tInfo.fX - m_tInfo.fCX * 0.5f) - ((int)cameraPos.x - (ML + MCX / 2))),
				((int)(m_tInfo.fY - m_tInfo.fCY * 0.5f) - ((int)cameraPos.y - (MT + MCY / 2))),
				(int)m_FrameMap[m_State].iFrameSizeX, //복사 사이즈
				(int)m_FrameMap[m_State].iFrameSizeY //복사 사이즈
			),
			(m_FrameMap[m_State].iFrameEnd - m_FrameMap[m_State].iFrameStart) * (int)m_FrameMap[m_State].iFrameSizeX,
			m_FrameMap[m_State].iMotion * (int)m_FrameMap[m_State].iFrameSizeY,
			(int)m_FrameMap[m_State].iFrameSizeX,
			(int)m_FrameMap[m_State].iFrameSizeY, //이미지 원본 사이즈
			Gdiplus::UnitPixel, &attr);
	}


}

void CObj::FrameRender_Size(HDC hDC, float _RatioX, float _RatioY)
{
	// 사용할 CBitmap
	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(m_FrameMap[m_State].AnimKey);
	Gdiplus::Bitmap* pImage;
	//사용할 이미지 Key 가져오기
	pImage = pBitMap->Get_Image();

	//카메라 위치(디폴트 -> 플레이어)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	// 캔버스
	Gdiplus::Graphics g(hDC);

	Gdiplus::ImageAttributes attr;
	attr.SetColorKey(Gdiplus::Color(255, 0, 255), Gdiplus::Color(255, 0, 255),
		Gdiplus::ColorAdjustTypeBitmap);

	if (m_fFrontAngle == 0)
	{
		g.DrawImage(pImage,
			Gdiplus::Rect(
				((int)(m_tInfo.fX - m_tInfo.fCX * 0.5f) - ((int)cameraPos.x - (ML + MCX / 2))),
				((int)(m_tInfo.fY - m_tInfo.fCY * 0.5f) - ((int)cameraPos.y - (MT + MCY / 2))),
				(int)m_FrameMap[m_State].iFrameSizeX * _RatioX, //복사 사이즈
				(int)m_FrameMap[m_State].iFrameSizeY * _RatioY //복사 사이즈
			),
			m_FrameMap[m_State].iFrameStart * (int)m_FrameMap[m_State].iFrameSizeX,
			m_FrameMap[m_State].iMotion * (int)m_FrameMap[m_State].iFrameSizeY,
			(int)m_FrameMap[m_State].iFrameSizeX,
			(int)m_FrameMap[m_State].iFrameSizeY, //이미지 원본 사이즈
			Gdiplus::UnitPixel, &attr);
	}
	else if (m_fFrontAngle == PI)
	{
		g.DrawImage(pImage,
			Gdiplus::Rect(
				((int)(m_tInfo.fX - m_tInfo.fCX * 0.5f) - ((int)cameraPos.x - (ML + MCX / 2))),
				((int)(m_tInfo.fY - m_tInfo.fCY * 0.5f) - ((int)cameraPos.y - (MT + MCY / 2))),
				(int)m_FrameMap[m_State].iFrameSizeX * _RatioX, //복사 사이즈
				(int)m_FrameMap[m_State].iFrameSizeY * _RatioY  //복사 사이즈
			),
			(m_FrameMap[m_State].iFrameEnd - m_FrameMap[m_State].iFrameStart) * (int)m_FrameMap[m_State].iFrameSizeX,
			m_FrameMap[m_State].iMotion * (int)m_FrameMap[m_State].iFrameSizeY,
			(int)m_FrameMap[m_State].iFrameSizeX,
			(int)m_FrameMap[m_State].iFrameSizeY, //이미지 원본 사이즈
			Gdiplus::UnitPixel, &attr);
	}
}



void CObj::RotateRender(HDC hDC, float _angle)
{
	//카메라 위치(디폴트 -> 플레이어)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	//사용할 이미지 Key 가져오기
	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(m_OneImgKey);
	Gdiplus::Bitmap* pImage;

	//사용할 이미지 Key 가져오기
	pImage = pBitMap->Get_Image();


	Gdiplus::Graphics g(hDC);

	g.TranslateTransform((int)m_tInfo.fX - ((int)cameraPos.x - (ML + MCX / 2))
		, (int)m_tInfo.fY - ((int)cameraPos.y - (MT + MCY / 2)));
	//rotate
	g.RotateTransform(_angle);
	g.TranslateTransform(-(int)m_tInfo.fX - ((int)cameraPos.x - (ML + MCX / 2))
		, -(int)m_tInfo.fY - ((int)cameraPos.y - (MT + MCY / 2)));

	//이미지 출력 (빠름, 알파블랜딩 X)
	g.DrawImage(pImage,
		Gdiplus::Rect(
			((int)(m_tInfo.fX - m_tInfo.fCX * 0.5f) + ((int)cameraPos.x - (ML + MCX / 2))),
			((int)(m_tInfo.fY - m_tInfo.fCY * 0.5f) + ((int)cameraPos.y - (MT + MCY / 2))),
			pImage->GetWidth(),  //복사 사이즈
			pImage->GetHeight()//복사 사이즈
		),
		0,
		0,
		pImage->GetWidth(),
		pImage->GetHeight(), //이미지 원본 사이즈
		Gdiplus::UnitPixel);

	g.ResetTransform();

}

//Rect 기준
void CObj::RotateFrameRender_Size(HDC hDC, float _angle, float _resizeX, float _resizeY)
{
	//카메라 위치(디폴트 -> 플레이어)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	//사용할 이미지 Key 가져오기
	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(m_FrameMap[m_State].AnimKey);
	Gdiplus::Bitmap* pImage;

	//사용할 이미지 Key 가져오기
	pImage = pBitMap->Get_Image();

	Gdiplus::Graphics g(hDC);

	g.TranslateTransform((int)m_tInfo.fX - ((int)cameraPos.x - (ML + MCX / 2))
		, (int)m_tInfo.fY - ((int)cameraPos.y - (MT + MCY / 2)));
	//rotate
	g.RotateTransform(_angle);
	g.TranslateTransform(-(int)m_tInfo.fX - ((int)cameraPos.x - (ML + MCX / 2))
		, -(int)m_tInfo.fY - ((int)cameraPos.y - (MT + MCY / 2)));


	Gdiplus::ImageAttributes attr;
	attr.SetColorKey(Gdiplus::Color(255, 0, 255), Gdiplus::Color(255, 0, 255),
		Gdiplus::ColorAdjustTypeBitmap);

	if (!m_FrameReverse)
	{
		g.DrawImage(pImage,
			Gdiplus::Rect(
				((int)m_tInfo.fX + ((int)cameraPos.x - (ML + MCX / 2))),
				((int)m_tInfo.fY + ((int)cameraPos.y - (MT + MCY / 2))),
				(int)m_FrameMap[m_State].iFrameSizeX * SMALL * _resizeX, //복사 사이즈
				(int)m_FrameMap[m_State].iFrameSizeY * SMALL * _resizeY),//복사 사이즈

			m_FrameMap[m_State].iMotion * (int)m_FrameMap[m_State].iFrameSizeX,
			m_FrameMap[m_State].iFrameStart * (int)m_FrameMap[m_State].iFrameSizeY,
			(int)m_FrameMap[m_State].iFrameSizeX,
			(int)m_FrameMap[m_State].iFrameSizeY, //이미지 원본 사이즈
			Gdiplus::UnitPixel, &attr);
	}
	else
	{
		g.DrawImage(pImage,
			Gdiplus::Rect(
				((int)m_tInfo.fX + ((int)cameraPos.x - (ML + MCX / 2))),
				((int)m_tInfo.fY + ((int)cameraPos.y - (MT + MCY / 2))),
				(int)m_FrameMap[m_State].iFrameSizeX * SMALL * _resizeX, //복사 사이즈
				(int)m_FrameMap[m_State].iFrameSizeY * SMALL * _resizeY),//복사 사이즈
			m_FrameMap[m_State].iMotion * (int)m_FrameMap[m_State].iFrameSizeX,
			(m_FrameMap[m_State].iFrameEnd - m_FrameMap[m_State].iFrameStart) * (int)m_FrameMap[m_State].iFrameSizeY,
			(int)m_FrameMap[m_State].iFrameSizeX,
			(int)m_FrameMap[m_State].iFrameSizeY, //이미지 원본 사이즈
			Gdiplus::UnitPixel, &attr);
	}


	g.ResetTransform();
}


//중심 기준
void CObj::RotateFrameRender(HDC hDC, float _angle)
{
	//카메라 위치(디폴트 -> 플레이어)
	fPOINT cameraPos = CSceneManager::Get_Instance()->GetCameraPos();

	//사용할 이미지 Key 가져오기
	CBitMap* pBitMap = CBmpMgr::Get_Instance()->Find_CBitMap(m_FrameMap[m_State].AnimKey);
	Gdiplus::Bitmap* pImage;

	//사용할 이미지 Key 가져오기
	pImage = pBitMap->Get_Image();


	Gdiplus::Graphics g(hDC);

	g.TranslateTransform((int)m_tInfo.fX - ((int)cameraPos.x - (ML + MCX / 2))
		, (int)m_tInfo.fY - ((int)cameraPos.y - (MT + MCY / 2)));
	//rotate
	g.RotateTransform(_angle);
	g.TranslateTransform(-(int)m_tInfo.fX - ((int)cameraPos.x - (ML + MCX / 2))
		, -(int)m_tInfo.fY - ((int)cameraPos.y - (MT + MCY / 2)));


	Gdiplus::ImageAttributes attr;
	attr.SetColorKey(Gdiplus::Color(255, 0, 255), Gdiplus::Color(255, 0, 255),
		Gdiplus::ColorAdjustTypeBitmap);


	g.DrawImage(pImage,
		Gdiplus::Rect(
			((int)m_tInfo.fX - (int)m_FrameMap[m_State].iFrameSizeX * 0.5f + ((int)cameraPos.x - (ML + MCX / 2))),
			((int)m_tInfo.fY - (int)m_FrameMap[m_State].iFrameSizeY * 0.5f + ((int)cameraPos.y - (MT + MCY / 2))),
			(int)m_FrameMap[m_State].iFrameSizeX, //복사 사이즈
			(int)m_FrameMap[m_State].iFrameSizeY),//복사 사이즈

		m_FrameMap[m_State].iFrameStart * (int)m_FrameMap[m_State].iFrameSizeX,
		m_FrameMap[m_State].iMotion * (int)m_FrameMap[m_State].iFrameSizeY,
		(int)m_FrameMap[m_State].iFrameSizeX,
		(int)m_FrameMap[m_State].iFrameSizeY, //이미지 원본 사이즈
		Gdiplus::UnitPixel, &attr);



	g.ResetTransform();
}



void CObj::Move_Frame()
{

	if (m_FrameMap[m_State].dwTime + m_FrameMap[m_State].dwSpeed < GetTickCount64())
	{
		++m_FrameMap[m_State].iFrameStart;

		if (m_FrameMap[m_State].iFrameStart > m_FrameMap[m_State].iFrameEnd)
			m_FrameMap[m_State].iFrameStart = 0;

		m_FrameMap[m_State].dwTime = GetTickCount64();
	}


}


//****************************Bitmap 컬러 정보 설정****************************/


Gdiplus::Bitmap* CObj::CloneBitmap(Gdiplus::Bitmap* sourceBitmap)
{
	// 현재 비트맵을 완전히 복사하여 새로운 비트맵을 생성
	Gdiplus::Bitmap* clonedBitmap = sourceBitmap->Clone(0, 0, sourceBitmap->GetWidth(), sourceBitmap->GetHeight(), sourceBitmap->GetPixelFormat());

	return clonedBitmap;
}

