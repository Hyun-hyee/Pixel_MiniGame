#include "stdafx.h"
#include "FontMgr.h"

CFontMgr* CFontMgr::m_pInstance = nullptr;

CFontMgr::CFontMgr()
	:m_MyFont()
{
}

CFontMgr::~CFontMgr()
{
	Release();
}

void CFontMgr::Initialize()
{
	wstring Filepath = L"../Resource/WireMan_Resource/Font/neodgm.ttf";
	 int err = AddFontResourceExW(Filepath.c_str(), FR_PRIVATE,0);

	LOGFONTW tFont = {};
	tFont.lfHeight = 16;
	tFont.lfCharSet = HANGEUL_CHARSET;
	tFont.lfPitchAndFamily = FIXED_PITCH;
	lstrcpyW(tFont.lfFaceName, L"MYFONT");
	m_MyFont = CreateFontIndirectW(&tFont);

	tFont = {};
	tFont.lfHeight = 50;
	tFont.lfCharSet = HANGEUL_CHARSET;
	tFont.lfPitchAndFamily = FIXED_PITCH;
	lstrcpyW(tFont.lfFaceName, L"MYBIGFONT");
	m_MyBigFont = CreateFontIndirectW(&tFont);

}

void CFontMgr::Release()
{
	RemoveFontResourceExW(L"MYFONT", FR_PRIVATE,0);

	DeleteObject(m_MyFont);
}

void CFontMgr::Draw_MyFont(HDC hDC, float _fLeft, float _fTop, float _fWidth, float _fHeight, wstring _Text)
{
	SetBkMode(hDC, 1);
	SetTextAlign(hDC, TA_CENTER);
	COLORREF TextColor = SetTextColor(hDC, RGB(255, 255, 255));
	HFONT Font = (HFONT)SelectObject(hDC, m_MyFont);
	RECT Rect = { (LONG)_fLeft, (LONG)_fTop, (LONG)(_fLeft + _fWidth), (LONG)(_fTop + _fHeight) };
	DrawTextW(hDC, _Text.c_str(), -1, &Rect, DT_NOCLIP | DT_LEFT);
	SetTextColor(hDC, TextColor);
	SelectObject(hDC, Font);
}

void CFontMgr::Draw_MyBigFont(HDC _hDC, float _fLeft, float _fTop, float _fWidth, float _fHeight, wstring _Text)
{
	SetBkMode(_hDC, 1);
	SetTextAlign(_hDC, TA_CENTER);
	COLORREF TextColor = SetTextColor(_hDC, RGB(255, 255, 255));
	HFONT Font = (HFONT)SelectObject(_hDC, m_MyBigFont);
	RECT Rect = { (LONG)_fLeft, (LONG)_fTop, (LONG)(_fLeft + _fWidth), (LONG)(_fTop + _fHeight) };
	DrawTextW(_hDC, _Text.c_str(), -1, &Rect, DT_NOCLIP | DT_LEFT);
	SetTextColor(_hDC, TextColor);
	SelectObject(_hDC, Font);
}

