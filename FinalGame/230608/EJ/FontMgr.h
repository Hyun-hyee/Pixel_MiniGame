#pragma once

class CFontMgr
{
private:
	CFontMgr();
	~CFontMgr();

	static CFontMgr* m_pInstance;

	HFONT m_MyFont;
	HFONT m_MyBigFont;


public:
	static CFontMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CFontMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	void Initialize();
	void Release();

	void Draw_MyFont(HDC _hDC, float _fLeft, float _fTop, float _fWidth, float _fHeight, wstring _Text);
	void Draw_MyBigFont(HDC _hDC, float _fLeft, float _fTop, float _fWidth, float _fHeight, wstring _Text);

};


