#include "stdafx.h"
#include "Bubble.h"
#include "SceneManager.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "BubbleGun.h"
#include "SoundMgr.h"

float a = 20.f;

vector<CObj*>		CBubble::PopBubbleList = {};
vector<CObj*>		CBubble::VisitedBubbleList = {};
int					CBubble::m_PlayerSoundCh = 0;

CBubble::CBubble()
{
	m_Type = BUBBLE;
}

CBubble::~CBubble()
{
	Release();
}

void CBubble::Initialize(void)
{
	m_fAngle = 0.f;
	m_fMoveAngle = 0.f;
	m_fSpeed = 12.f;
	m_fAccel = 1.f;
	bMove = true;
	bShoot = false;
	bFall = false;
	bTop = false;
	fDownDistance = 40.f;

	AddPoint(-(a+2.f) / 2.f,-(a + 2.f) * sin(D3DX_PI / 3.f));
	AddPoint((a+2.f) / 2.f, -(a + 2.f) * sin(D3DX_PI / 3.f));
	AddPoint((a+2.f) * 3 / 4.f, -(a + 2.f) * sin(D3DX_PI / 3.f)* 0.75f);
	AddPoint((a+2.f) , 0.f);
	AddPoint((a+2.f) * 3 / 4.f, (a + 2.f) * sin(D3DX_PI / 3.f) * 0.75f);
	AddPoint((a+2.f) / 2.f, (a + 2.f) * sin(D3DX_PI / 3.f));
	AddPoint(-(a+2.f) / 2.f, (a + 2.f) * sin(D3DX_PI / 3.f));
	AddPoint(-(a+2.f) * 3 / 4.f, (a + 2.f) * sin(D3DX_PI / 3.f) * 0.75f);
	AddPoint(-(a+2.f), 0.f);
	AddPoint(-(a+2.f) * 3 / 4.f, -(a + 2.f) * sin(D3DX_PI / 3.f) * 0.75f);

	InitImage();

	for (int i = 0; i < 6; ++i)
		AdjacentBubbleList[i] = nullptr;
}

void CBubble::Update(void)
{ 
	if (bShoot && !bFall)
	{
		m_vInfo.vPos.x += cos(m_fMoveAngle) * m_fSpeed;
		m_vInfo.vPos.y -= sin(m_fMoveAngle) * m_fSpeed;
	}
	else if (bShoot && bFall && m_State != BUBBLE_RED_POP && m_State != BUBBLE_GREEN_POP && m_State != BUBBLE_BLUE_POP && m_State != BUBBLE_YELLOW_POP && m_State != BUBBLE_PURPLE_POP)
	{
		m_vInfo.vPos.y += 12.f * m_fAccel;
		m_fAccel += 0.2f;

		if (m_vInfo.vPos.y >= MB + 100.f)
			m_State = DEAD;
	}

	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vInfo.vPos.x, m_vInfo.vPos.y, 0.f);

	m_vInfo.matWorld = matScale * matRotZ * matTrans;

	CObj::UpdatePoint();
	__super::Update_Rect();

	StateUpdate();
	CObj::Move_Frame();
}

void CBubble::LateUpdate(void)
{
}

void CBubble::Render(HDC hDC)
{
	CObj::FrameRender(hDC);
//	CObj::CollideRender(hDC);
}

void CBubble::Release(void)
{
}

void CBubble::InitImage()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bubble_Red.bmp", L"BUBBLE_RED");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bubble_Green.bmp", L"BUBBLE_GREEN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bubble_Blue.bmp", L"BUBBLE_BLUE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bubble_Yellow.bmp", L"BUBBLE_YELLOW");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bubble_Purple.bmp", L"BUBBLE_PURPLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bubble_Gray.bmp", L"BUBBLE_GRAY");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/R.png", L"BUBBLE_RED_POP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/G.png", L"BUBBLE_GREEN_POP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/B.png", L"BUBBLE_BLUE_POP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Y.png", L"BUBBLE_YELLOW_POP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/P.png", L"BUBBLE_PURPLE_POP");

	FRAME TempFrame;
	TempFrame.AnimKey = L"BUBBLE_RED";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 1;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 300;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 40;
	TempFrame.iFrameSizeY = 40;

	m_FrameMap.insert({ BUBBLE_RED, TempFrame });

	TempFrame.AnimKey = L"BUBBLE_GREEN";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 1;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 300;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 40;
	TempFrame.iFrameSizeY = 40;

	m_FrameMap.insert({ BUBBLE_GREEN, TempFrame });

	TempFrame.AnimKey = L"BUBBLE_BLUE";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 1;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 300;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 40;
	TempFrame.iFrameSizeY = 40;

	m_FrameMap.insert({ BUBBLE_BLUE, TempFrame });

	TempFrame.AnimKey = L"BUBBLE_YELLOW";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 1;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 300;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 40;
	TempFrame.iFrameSizeY = 40;

	m_FrameMap.insert({ BUBBLE_YELLOW, TempFrame });

	TempFrame.AnimKey = L"BUBBLE_PURPLE";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 1;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 300;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 40;
	TempFrame.iFrameSizeY = 40;

	m_FrameMap.insert({ BUBBLE_PURPLE, TempFrame });


	TempFrame.AnimKey = L"BUBBLE_RED_POP";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 2;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 50;
	TempFrame.iFrameSizeY = 50;

	m_FrameMap.insert({ BUBBLE_RED_POP, TempFrame });

	TempFrame.AnimKey = L"BUBBLE_GREEN_POP";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 2;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 50;
	TempFrame.iFrameSizeY = 50;

	m_FrameMap.insert({ BUBBLE_GREEN_POP, TempFrame });

	TempFrame.AnimKey = L"BUBBLE_BLUE_POP";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 2;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 50;
	TempFrame.iFrameSizeY = 50;

	m_FrameMap.insert({ BUBBLE_BLUE_POP, TempFrame });

	TempFrame.AnimKey = L"BUBBLE_YELLOW_POP";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 2;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 50;
	TempFrame.iFrameSizeY = 50;

	m_FrameMap.insert({ BUBBLE_YELLOW_POP, TempFrame });

	TempFrame.AnimKey = L"BUBBLE_PURPLE_POP";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 2;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 50;
	TempFrame.iFrameSizeY = 50;

	m_FrameMap.insert({ BUBBLE_PURPLE_POP, TempFrame });

	TempFrame.AnimKey = L"BUBBLE_GRAY";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 40;
	TempFrame.iFrameSizeY = 40;

	m_FrameMap.insert({ BUBBLE_GRAY, TempFrame });
}

void CBubble::StateUpdate()
{
	if (m_PrevState != m_State)
	{
		m_FrameMap[m_State].iFrameStart = 0;
		m_FrameMap[m_State].dwTime = GetTickCount64();
	}

	switch (m_State)
	{
	case BUBBLE_RED_POP:
	case BUBBLE_GREEN_POP:
	case BUBBLE_BLUE_POP:
	case BUBBLE_YELLOW_POP:
	case BUBBLE_PURPLE_POP:
		if (m_FrameMap[m_State].iFrameStart >= m_FrameMap[m_State].iFrameEnd)
			m_State = DEAD;
		break;
	}

	m_PrevState = m_State;

}



int CBubble::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();

	if (bShoot)
	{
		if (targetType == WALL)
		{
			if (_dir.y >= -0.4f && _dir.y <= 0.4f)
			{
 				//m_vInfo.vPos.x -= cos(m_fMoveAngle) * 0.9f * m_fSpeed;
				//m_vInfo.vPos.y += sin(m_fMoveAngle) * 0.9f * m_fSpeed;
				m_fSpeed = 0.f;

				int i = ((m_vInfo.vPos.x - ML - a) / (2 * a)) + 1;
				if (i <= 6)
					i = 7;
				else if (i >= 15)
					i = 14;
				m_vInfo.vPos.x = ML + 2 * a * i;
				//m_vInfo.vPos.y = MT + 70 +  a * sin(PI / 3.f);
				m_vInfo.vPos.y = _target->GetPosY() + 35 + a * sin(PI / 3.f);
				bMove = false;

				bTop = true;
			}
			else
				m_fMoveAngle = PI - m_fMoveAngle;
		}

		if (targetType == BUBBLE)
		{
			if (_target->Get_State() != BUBBLE_RED_POP && _target->Get_State() != BUBBLE_GREEN_POP && _target->Get_State() != BUBBLE_BLUE_POP && _target->Get_State() != BUBBLE_YELLOW_POP && _target->Get_State() != BUBBLE_PURPLE_POP && _target->Get_State() != DEAD
				&& dynamic_cast<CBubble*> (_target)->GetFall() != true)
			{
				if (dynamic_cast<CBubble*> (_target)->GetShoot())
				{

					float Degree;
					//쏠때 충돌 후 고정
					if (targetType == BUBBLE && bMove)
					{
						//겹치는거 보정
						//m_vInfo.vPos.x -= cos(m_fMoveAngle) * 0.8f * m_fSpeed;
						//m_vInfo.vPos.y += sin(m_fMoveAngle) * 0.8f * m_fSpeed;

						D3DXVECTOR3 TargetPos = _target->Get_vInfo()->vPos;
						D3DXVECTOR3 Temp = TargetPos - m_vInfo.vPos;
						D3DXVec3Normalize(&Temp, &Temp);
						D3DXVECTOR3 axisX = { 1.f,0.f,0.f };
						float collisionAngle = acosf(D3DXVec3Dot(&Temp, &axisX));

						Degree = D3DXToDegree(collisionAngle);

						if (Temp.y > 0.f)
							Degree = 360.f - Degree;

						if (Degree < 90.f && Degree >= 30.f)
						{
							if (dynamic_cast<CBubble*>(_target)->GetAdjacentList(0) != nullptr && dynamic_cast<CBubble*>(_target)->GetAdjacentList(0) != this)
								return 0;
							SetPos(TargetPos.x - a, TargetPos.y + 2 * a * sin(PI / 3.f));
							AdjacentBubbleList[4] = dynamic_cast<CBubble*>(_target)->GetAdjacentList(2);
							AdjacentBubbleList[3] = dynamic_cast<CBubble*>(_target)->GetAdjacentList(1);
						}
						else if (Degree < 150.f && Degree >= 90.f)
						{
							if (dynamic_cast<CBubble*>(_target)->GetAdjacentList(1) != nullptr && dynamic_cast<CBubble*>(_target)->GetAdjacentList(1) != this)
								return 0;
							SetPos(TargetPos.x + a, TargetPos.y + 2 * a * sin(PI / 3.f));
							AdjacentBubbleList[2] = dynamic_cast<CBubble*>(_target)->GetAdjacentList(0);
							AdjacentBubbleList[5] = dynamic_cast<CBubble*>(_target)->GetAdjacentList(3);
						}
						else if (Degree < 210.f && Degree >= 150.f)
						{
							if (dynamic_cast<CBubble*>(_target)->GetAdjacentList(3) != nullptr && dynamic_cast<CBubble*>(_target)->GetAdjacentList(3) != this)
								return 0;
							SetPos(TargetPos.x + 2 * a, TargetPos.y);
							AdjacentBubbleList[0] = dynamic_cast<CBubble*>(_target)->GetAdjacentList(1);
							AdjacentBubbleList[4] = dynamic_cast<CBubble*>(_target)->GetAdjacentList(5);
						}
						else if (Degree < 30.f || Degree >= 330.f)
						{
							if (dynamic_cast<CBubble*>(_target)->GetAdjacentList(2) != nullptr && dynamic_cast<CBubble*>(_target)->GetAdjacentList(2) != this)
								return 0;
							SetPos(TargetPos.x - 2 * a, TargetPos.y);
							AdjacentBubbleList[1] = dynamic_cast<CBubble*>(_target)->GetAdjacentList(0);
							AdjacentBubbleList[5] = dynamic_cast<CBubble*>(_target)->GetAdjacentList(4);
						}
						else if (Degree < 270.f && Degree >= 210.f)
						{
							if (dynamic_cast<CBubble*>(_target)->GetAdjacentList(5) != nullptr && dynamic_cast<CBubble*>(_target)->GetAdjacentList(5) != this)
								return 0;
							SetPos(TargetPos.x - a, TargetPos.y - 2 * a * sin(PI / 3.f));
							AdjacentBubbleList[1] = dynamic_cast<CBubble*>(_target)->GetAdjacentList(3);
							AdjacentBubbleList[2] = dynamic_cast<CBubble*>(_target)->GetAdjacentList(4);
						}
						else if (Degree < 330.f && Degree >= 270.f)
						{
							if (dynamic_cast<CBubble*>(_target)->GetAdjacentList(4) != nullptr && dynamic_cast<CBubble*>(_target)->GetAdjacentList(4) != this)
								return 0;
							SetPos(TargetPos.x + a, TargetPos.y - 2 * a * sin(PI / 3.f));
							AdjacentBubbleList[0] = dynamic_cast<CBubble*>(_target)->GetAdjacentList(2);
							AdjacentBubbleList[3] = dynamic_cast<CBubble*>(_target)->GetAdjacentList(5);
						}

						m_fSpeed = 0.f;
						bMove = false;
					}
					//인접 리스트 삽입
					D3DXVECTOR3 TargetPos = _target->Get_vInfo()->vPos;
					D3DXVECTOR3 Temp = TargetPos - m_vInfo.vPos;
					D3DXVec3Normalize(&Temp, &Temp);
					D3DXVECTOR3 axisX = { 1.f,0.f,0.f };
					float collisionAngle = acosf(D3DXVec3Dot(&Temp, &axisX));

					Degree = D3DXToDegree(collisionAngle);

					if (Temp.y > 0.f)
						Degree = 360.f - Degree;

					if (Degree < 90.f && Degree >= 30.f)
					{
						if (AdjacentBubbleList[5] == nullptr)
							AdjacentBubbleList[5] = _target;
					}
					else if (Degree < 150.f && Degree >= 90.f)
					{
						if (AdjacentBubbleList[4] == nullptr)
							AdjacentBubbleList[4] = _target;
					}
					else if (Degree < 210.f && Degree >= 150.f)
					{
						if (AdjacentBubbleList[2] == nullptr)
							AdjacentBubbleList[2] = _target;
					}
					else if (Degree < 30.f || Degree >= 330.f)
					{
						if (AdjacentBubbleList[3] == nullptr)
							AdjacentBubbleList[3] = _target;
					}
					else if (Degree < 270.f && Degree >= 210.f)
					{
						if (AdjacentBubbleList[0] == nullptr)
							AdjacentBubbleList[0] = _target;
					}
					else if (Degree < 330.f && Degree >= 270.f)
					{
						if (AdjacentBubbleList[1] == nullptr)
							AdjacentBubbleList[1] = _target;
					}
				}
			}
		}
			
	}
	return 0;
}

int CBubble::OutCollision(CObj* _target)
{
	
	return 0;
}

int CBubble::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();
	
	if (targetType == BUBBLE && bShoot)
	{
		if (dynamic_cast<CBubble*> (_target)->GetShoot())
		{
			if (_target->Get_State() != BUBBLE_RED_POP && _target->Get_State() != BUBBLE_GREEN_POP && _target->Get_State() != BUBBLE_BLUE_POP && _target->Get_State() != BUBBLE_YELLOW_POP && _target->Get_State() != BUBBLE_PURPLE_POP && _target->Get_State() != DEAD
				&& dynamic_cast<CBubble*> (_target)->GetFall() != true)
			{
				//인접 리스트 삽입
				D3DXVECTOR3 TargetPos = _target->Get_vInfo()->vPos;
				D3DXVECTOR3 Temp = TargetPos - m_vInfo.vPos;
				D3DXVec3Normalize(&Temp, &Temp);
				D3DXVECTOR3 axisX = { 1.f,0.f,0.f };
				float collisionAngle = acosf(D3DXVec3Dot(&Temp, &axisX));

				float Degree = D3DXToDegree(collisionAngle);

				if (Temp.y > 0.f)
					Degree = 360.f - Degree;

				if (Degree < 90.f && Degree >= 30.f)
				{
					if (AdjacentBubbleList[5] == nullptr)
						AdjacentBubbleList[5] = _target;
				}
				else if (Degree < 150.f && Degree >= 90.f)
				{
					if (AdjacentBubbleList[4] == nullptr)
						AdjacentBubbleList[4] = _target;
				}
				else if (Degree < 210.f && Degree >= 150.f)
				{
					if (AdjacentBubbleList[2] == nullptr)
						AdjacentBubbleList[2] = _target;
				}
				else if (Degree < 30.f || Degree >= 330.f)
				{
					if (AdjacentBubbleList[3] == nullptr)
						AdjacentBubbleList[3] = _target;
				}
				else if (Degree < 270.f && Degree >= 210.f)
				{
					if (AdjacentBubbleList[0] == nullptr)
						AdjacentBubbleList[0] = _target;
				}
				else if (Degree < 330.f && Degree >= 270.f)
				{
					if (AdjacentBubbleList[1] == nullptr)
						AdjacentBubbleList[1] = _target;
				}

			}
		}

			
		
	}
	

	return 0;
}

void CBubble::FindPopBubble(vector<CObj*>& _popList, vector<CObj*>& _vistedList, OBJSTATE _color)
{
	_vistedList.push_back(this);
	if (m_State == _color)
		_popList.push_back(this);
	else
		return;

	for (auto& iter1 : AdjacentBubbleList)
	{
		bool Check = true;
		if (iter1 != nullptr)
		{
			if (iter1->Get_State() != BUBBLE_RED_POP && iter1->Get_State() != BUBBLE_GREEN_POP && iter1->Get_State() != BUBBLE_BLUE_POP && iter1->Get_State() != BUBBLE_YELLOW_POP && iter1->Get_State() != BUBBLE_PURPLE_POP && iter1->Get_State() != DEAD)
			{
				for (auto& iter2 : _vistedList)
				{
					if (iter1 == iter2)
						Check = false;
				}
				if (Check)
					dynamic_cast<CBubble*>(iter1)->FindPopBubble(_popList, _vistedList, _color);

			}
		}
	}
	return;
}

void CBubble::FindTopBubble(bool &_TopCheck, vector<CObj*>& _vistedList)
{
	_vistedList.push_back(this);
	if (bTop)
	{
		_TopCheck = true;
		return;
	}

	for (int i = 0; i < 6; ++i)
	{
		bool Check = true;
		if (AdjacentBubbleList[i] != nullptr)
		{
			if (AdjacentBubbleList[i]->Get_State() != BUBBLE_RED_POP && AdjacentBubbleList[i]->Get_State() != BUBBLE_GREEN_POP && AdjacentBubbleList[i]->Get_State() != BUBBLE_BLUE_POP && AdjacentBubbleList[i]->Get_State() != BUBBLE_YELLOW_POP && AdjacentBubbleList[i]->Get_State() != BUBBLE_PURPLE_POP && AdjacentBubbleList[i]->Get_State() != DEAD)
			{
				for (auto& iter : _vistedList)
				{
					if (AdjacentBubbleList[i] == iter)
						Check = false;
				}
				if (Check)
					dynamic_cast<CBubble*>(AdjacentBubbleList[i])->FindTopBubble(_TopCheck, _vistedList);
			}
		}
	}
}

void CBubble::PopBubble()
{
	if (PopBubbleList.size() >= 3)
	{
		PlayerPlaySound(L"Bubble_Pop.wav");
		
		for (auto& iter : PopBubbleList)
		{
			dynamic_cast<CBubble*>(iter)->SetPopColor();
		}
		list <CObj*>* BubbleList = CObjMgr::Get_Instance()->Get_ObjList(BUBBLE);
		for (auto& iter : *BubbleList)
		{
			bool CheckTop = false;
			vector<CObj*> VisitedList;
			dynamic_cast<CBubble*>(iter)->FindTopBubble(CheckTop, VisitedList);

			if (CheckTop == false && dynamic_cast<CBubble*> (iter)->GetShoot())
				dynamic_cast<CBubble*> (iter)->SetFall(true);

			VisitedList.clear();
		}
		for (auto& iter : *BubbleList)
		{
			dynamic_cast<CBubble*> (iter)->ResetAdjacentList();
		}
		dynamic_cast<CBubbleGun*> (CObjMgr::Get_Instance()->Get_Player())->ResetLastBubble();
		
	}
}

void CBubble::SetPopColor()
{
	switch (m_State)
	{
	case BUBBLE_RED:
		m_State = BUBBLE_RED_POP;
		break;

	case BUBBLE_GREEN:
		m_State = BUBBLE_GREEN_POP;
		break;

	case BUBBLE_BLUE:
		m_State = BUBBLE_BLUE_POP;
		break;

	case BUBBLE_YELLOW:
		m_State = BUBBLE_YELLOW_POP;
		break;

	case BUBBLE_PURPLE:
		m_State = BUBBLE_PURPLE_POP;
		break;
	default:
		break;
	}
}

void CBubble::ResetAdjacentList()
{
	for (int i = 0; i < 6; ++i)
	{
		if (AdjacentBubbleList[i] != nullptr)
		{
			if (AdjacentBubbleList[i]->Get_State() == DEAD || AdjacentBubbleList[i]->Get_State() ==  BUBBLE_RED_POP || AdjacentBubbleList[i]->Get_State() == BUBBLE_GREEN_POP || AdjacentBubbleList[i]->Get_State() == BUBBLE_BLUE_POP || AdjacentBubbleList[i]->Get_State() == BUBBLE_YELLOW_POP || AdjacentBubbleList[i]->Get_State() == BUBBLE_PURPLE_POP
				|| dynamic_cast<CBubble*> (AdjacentBubbleList[i])->GetFall() == true)
 				AdjacentBubbleList[i] = nullptr;
		}
	}
}

void CBubble::PlayerPlaySound(TCHAR* _name)
{
	if (m_PlayerSoundCh == 0)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER, SOUND_POP1);
	else if (m_PlayerSoundCh == 1)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER2, SOUND_POP2);
	else if (m_PlayerSoundCh == 2)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER3, SOUND_POP3);
	else if (m_PlayerSoundCh == 3)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER4, SOUND_POP4);

	++m_PlayerSoundCh;
	if (m_PlayerSoundCh == 4)
		m_PlayerSoundCh = 0;
}