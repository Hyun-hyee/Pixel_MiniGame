#pragma once
#include "Tile.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

	static CTileMgr* m_pInstance;

public:
	static CTileMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTileMgr;
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
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	void Change_Tile();

	void Save_Tile();
	void Load_Tile();

	vector<CTile*> Get_vecTile() { return m_vecTIle; }	

private:
	vector<CTile*> m_vecTIle;
	

};

