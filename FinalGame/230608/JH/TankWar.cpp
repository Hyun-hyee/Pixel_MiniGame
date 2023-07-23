#include "stdafx.h"
#include "TankWar.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "Player.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "Define.h"
#include "SceneManager.h"
#include "Wall.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "Tank.h"
#include "Enemy.h"
CTankWar::CTankWar()
{
	m_bCreate1 = true;
	m_bCreate2 = true;
	m_bCreate3 = true;
}

CTankWar::~CTankWar()
{
	Release();
}

void CTankWar::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp_Background(L"../Resource/JH/TankBack.bmp", L"TankWarBack");
	CSceneManager::Get_Instance()->Set_BackSize({ 1050, 4000 });
	Set_BackGroundKey(L"TankWarBack");
	Create_Wall();

	//BGM
	CSoundMgr::Get_Instance()->StopAll();
	//CSoundMgr::Get_Instance()->PlayBGM(L"song_killyourtv.ogg", SOUND_VOL1);
	//m_BGMkey = L"song_killyourtv.ogg";

		//캐릭터 생성
	CObj* Temp = CObjFactory<CTank>::Create();
	CObjMgr::Get_Instance()->Add_Object(TANK, Temp);

	Temp = CObjFactory<CEnemy>::Create();
	Temp->SetPos(720.f+ML, 3500.f+MT);
	CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

	//Temp = CObjFactory<CEnemy>::Create();
	//Temp->SetPos(100.f + ML, 3550.f + MT);
	//CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

	//Temp = CObjFactory<CEnemy>::Create();
	//Temp->SetPos(110.f + ML, 3250.f + MT);
	//CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

	//Temp = CObjFactory<CEnemy>::Create();
	//Temp->SetPos(720.f + ML, 3200.f + MT);
	//CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

	//Temp = CObjFactory<CEnemy>::Create();
	//Temp->SetPos(170.f + ML, 3030.f + MT);
	//CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

}

void CTankWar::Update()
{
	float fTankY = CObjMgr::Get_Instance()->Get_Tank()->Get_vInfo()->vPos.y;
	if (3400 >= fTankY&&m_bCreate1)
	{

		CObj* Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(700.f + ML, 2850.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(370.f + ML, 2700.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(840.f + ML, 2600.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(370.f + ML, 2290.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);
		m_bCreate1 = false;
	}
	if (2600 >= fTankY && m_bCreate2)
	{
		CObj* Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(700.f + ML, 2100.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(150.f + ML, 1850.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(700.f + ML, 1800.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(600.f + ML, 1500.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(600.f + ML, 1100.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(170.f + ML, 970.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(860.f + ML, 960.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);


		m_bCreate2 = false;
	}
	if (1200 >= fTankY && m_bCreate3)
	{
		CObj* Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(150.f + ML, 660.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(850.f + ML, 650.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(470.f + ML, 520.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);
		Temp = CObjFactory<CEnemy>::Create();

		Temp->SetPos(480.f + ML, 260.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(260.f + ML, 200.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		Temp = CObjFactory<CEnemy>::Create();
		Temp->SetPos(720.f + ML, 200.f + MT);
		CObjMgr::Get_Instance()->Add_Object(ENEMY, Temp);

		m_bCreate3 = false;

	}
	CObjMgr::Get_Instance()->Update();
}

void CTankWar::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CTankWar::Render(HDC _hDC)
{
	BackGroundRender(_hDC);
	CObjMgr::Get_Instance()->Render(_hDC);
}

void CTankWar::Release()
{
}

void CTankWar::Create_Wall()
{
	//1초록탱크
	CObj* Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(120 + ML, 3730 + MT);
	Temp->AddPoint(225 + ML, 3730 + MT);
	Temp->AddPoint(225 + ML, 3780 + MT);
	Temp->AddPoint(120 + ML, 3780 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//2처음건물
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(220 + ML, 3490 + MT);
	Temp->AddPoint(560 + ML, 3490 + MT);
	Temp->AddPoint(560 + ML, 3625 + MT);
	Temp->AddPoint(220 + ML, 3625 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//3빨간차
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(670 + ML, 3465 + MT);
	Temp->AddPoint(780 + ML, 3465 + MT);
	Temp->AddPoint(780 + ML, 3485 + MT);
	Temp->AddPoint(670 + ML, 3485 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	
	//4우측 건물 두개
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(890 + ML, 3280 + MT);
	Temp->AddPoint(1000 + ML, 3280 + MT);
	Temp->AddPoint(1000 + ML, 3415 + MT);
	Temp->AddPoint(890 + ML, 3415 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//5왼쪽 건물 하나
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(335 + ML, 3280 + MT);
	Temp->AddPoint(560 + ML, 3280 + MT);
	Temp->AddPoint(560 + ML, 3410 + MT);
	Temp->AddPoint(110 + ML, 3410 + MT);
	Temp->AddPoint(110 + ML, 3360 + MT);
	Temp->AddPoint(335 + ML, 3360 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//6 우측 건물 두개
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(890 + ML, 3040 + MT);
	Temp->AddPoint(1000 + ML, 3040 + MT);
	Temp->AddPoint(1000 + ML, 3200 + MT);
	Temp->AddPoint(890 + ML, 3200 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//7 좌측 건물 두개
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(220 + ML, 3060 + MT);
	Temp->AddPoint(560 + ML, 3060 + MT);
	Temp->AddPoint(560 + ML, 3200 + MT);
	Temp->AddPoint(220 + ML, 3200 + MT);

	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//8 우측 건물
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(890 + ML, 2820 + MT);
	Temp->AddPoint(1000 + ML, 2820 + MT);
	Temp->AddPoint(1000 + ML, 2990 + MT);
	Temp->AddPoint(890 + ML, 2990 + MT);

	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//9 좌측건물 두개
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(0 + ML, 2825 + MT);
	Temp->AddPoint(560 + ML, 2825 + MT);
	Temp->AddPoint(560 + ML, 2990 + MT);
	Temp->AddPoint(0 + ML, 2990 + MT);

	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//	10벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(890 + ML, 2600 + MT);
	Temp->AddPoint(1000 + ML, 2600 + MT);
	Temp->AddPoint(1000 + ML, 2750 + MT);
	Temp->AddPoint(890 + ML, 2750 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//	11벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(560 + ML, 2610 + MT);
	Temp->AddPoint(780 + ML, 2610 + MT);
	Temp->AddPoint(780 + ML, 2740 + MT);
	Temp->AddPoint(560 + ML, 2740 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//11번벽 
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(560 + ML, 2320 + MT);
	Temp->AddPoint(790 + ML, 2320 + MT);
	Temp->AddPoint(790 + ML, 2400 + MT);
	Temp->AddPoint(560 + ML, 2400 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

			
//	12벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(0 + ML, 2480 + MT);
	Temp->AddPoint(220 + ML, 2480 + MT);
	Temp->AddPoint(220 + ML, 2740 + MT);
	Temp->AddPoint(0 + ML, 2740 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//	13벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(560 + ML, 2480 + MT);
	Temp->AddPoint(900 + ML, 2480 + MT);
	Temp->AddPoint(900 + ML, 2535 + MT);
	Temp->AddPoint(560 + ML, 2535 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//	14벽				
	//Temp = CObjFactory<CWall>::Create();
	//Temp->AddPoint(560 + ML, 2320 + MT);
	//Temp->AddPoint(790 + ML, 2320 + MT);
	//Temp->AddPoint(790 + ML, 2400 + MT);
	//Temp->AddPoint(560 + ML, 2400 + MT);
	//CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	15벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(560 + ML, 2245 + MT);
	Temp->AddPoint(1005 + ML, 2245 + MT);
	Temp->AddPoint(1005 + ML, 2305 + MT);
	Temp->AddPoint(560 + ML, 2305 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	16벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(890 + ML, 2240 + MT);
	Temp->AddPoint(1000 + ML, 2240 + MT);
	Temp->AddPoint(1000 + ML, 2400 + MT);
	Temp->AddPoint(890 + ML, 2400 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//	17벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(0 + ML, 2240 + MT);
	Temp->AddPoint(230 + ML, 2240 + MT);
	Temp->AddPoint(230 + ML, 2400 + MT);
	Temp->AddPoint(0 + ML, 2400 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	18벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(0 + ML, 2030 + MT);
	Temp->AddPoint(115 + ML, 2030 + MT);
	Temp->AddPoint(115 + ML, 2165 + MT);
	Temp->AddPoint(0 + ML, 2165 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	19벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(230 + ML, 2030 + MT);
	Temp->AddPoint(570 + ML, 2030 + MT);
	Temp->AddPoint(570 + ML, 2170 + MT);
	Temp->AddPoint(230 + ML, 2170 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	?번				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(0 + ML, 3070 + MT);
	Temp->AddPoint(120 + ML, 3070 + MT);
	Temp->AddPoint(120 + ML, 3200 + MT);
	Temp->AddPoint(0 + ML, 3200 + MT);
	CObjMgr::Get_Instance()->Add_Object(OBJ_NONE, Temp);

	//	20벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(895 + ML, 2030 + MT);
	Temp->AddPoint(1000 + ML, 2030 + MT);
	Temp->AddPoint(1000 + ML, 2170 + MT);
	Temp->AddPoint(895 + ML, 2170 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	21벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(890 + ML, 1815 + MT);
	Temp->AddPoint(1000 + ML, 1815 + MT);
	Temp->AddPoint(1000 + ML, 1950 + MT);
	Temp->AddPoint(890 + ML, 1950 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//	22벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(335 + ML, 1810 + MT);
	Temp->AddPoint(560 + ML, 1810 + MT);
	Temp->AddPoint(560 + ML, 1945 + MT);
	Temp->AddPoint(335 + ML, 1945 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	23벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(520 + ML, 1895 + MT);
	Temp->AddPoint(780 + ML, 1895 + MT);
	Temp->AddPoint(780 + ML, 1945 + MT);
	Temp->AddPoint(520 + ML, 1945 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	24벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(780 + ML, 1385 + MT);
	Temp->AddPoint(1000 + ML, 1385 + MT);
	Temp->AddPoint(1000 + ML, 1735 + MT);
	Temp->AddPoint(780 + ML, 1735 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	25벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(0 + ML, 1385 + MT);
	Temp->AddPoint(450 + ML, 1385 + MT);
	Temp->AddPoint(450 + ML, 1715 + MT);
	Temp->AddPoint(0 + ML, 1715 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	26벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(780 + ML, 1040 + MT);
	Temp->AddPoint(1000 + ML, 1040 + MT);
	Temp->AddPoint(1000 + ML, 1310 + MT);
	Temp->AddPoint(780 + ML, 1310 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	27벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(0 + ML, 1040 + MT);
	Temp->AddPoint(450 + ML, 1040 + MT);
	Temp->AddPoint(450 + ML, 1310 + MT);
	Temp->AddPoint(0 + ML, 1310 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//	28벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(890 + ML, 690 + MT);
	Temp->AddPoint(1000 + ML, 690 + MT);
	Temp->AddPoint(1000 + ML, 880 + MT);
	Temp->AddPoint(890 + ML, 880 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
			
	//	29벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(0 + ML, 690 + MT);
	Temp->AddPoint(785 + ML, 690 + MT);
	Temp->AddPoint(785 + ML, 880 + MT);
	Temp->AddPoint(0 + ML, 880 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//	30벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(670 + ML, 450 + MT);
	Temp->AddPoint(1000 + ML, 450 + MT);
	Temp->AddPoint(1000 + ML, 610 + MT);
	Temp->AddPoint(670 + ML, 610 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	31벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(0 + ML, 450 + MT);
	Temp->AddPoint(340 + ML, 450 + MT);
	Temp->AddPoint(340 + ML, 610 + MT);
	Temp->AddPoint(0 + ML, 610 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	32벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(670 + ML, 240 + MT);
	Temp->AddPoint(1000 + ML, 240 + MT);
	Temp->AddPoint(1000 + ML, 375 + MT);
	Temp->AddPoint(670 + ML, 375 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	33벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(110 + ML, 240 + MT);
	Temp->AddPoint(335 + ML, 240 + MT);
	Temp->AddPoint(335 + ML, 375 + MT);
	Temp->AddPoint(110 + ML, 375 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	34벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(0 + ML, 290 + MT);
	Temp->AddPoint(130 + ML, 290 + MT);
	Temp->AddPoint(130 + ML, 370 + MT);
	Temp->AddPoint(0 + ML, 370 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	35벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(0 + ML, 0 + MT);
	Temp->AddPoint(340 + ML, 0 + MT);
	Temp->AddPoint(340 + ML, 160 + MT);
	Temp->AddPoint(0 + ML, 160 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	36벽				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(670 + ML, 0 + MT);
	Temp->AddPoint(1000 + ML, 0 + MT);
	Temp->AddPoint(1000 + ML, 160 + MT);
	Temp->AddPoint(670 + ML, 160 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);

	//긴 왼벽
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(-100 + ML, -100 + MT);
	Temp->AddPoint(0 + ML, -100 + MT);
	Temp->AddPoint(0 + ML, 4200 + MT);
	Temp->AddPoint(-100 + ML, 4200 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//// 긴 오른벽
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(990 + ML, -100 + MT);
	Temp->AddPoint(1200 + ML, -100 + MT);
	Temp->AddPoint(1200 + ML, 4200 + MT);
	Temp->AddPoint(990 + ML, 4200 + MT);
	CObjMgr::Get_Instance()->Add_Object(WALL, Temp);
	//	END				
	Temp = CObjFactory<CWall>::Create();
	Temp->AddPoint(410 + ML, 120 + MT);
	Temp->AddPoint(590 + ML, 120 + MT);
	Temp->AddPoint(590 + ML, 155 + MT);
	Temp->AddPoint(410 + ML, 155 + MT);
	CObjMgr::Get_Instance()->Add_Object(OBJ_NONE, Temp);

}
