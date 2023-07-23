#include "stdafx.h"
#include "SkiingPlayer.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "SceneManager.h"
#include "BmpMgr.h"
#include "BitMap.h"
#include "CameraComponent.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "ObjFactory.h"
#include "CameraComponent.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "SkiingFlag.h"

CSkiingPlayer::CSkiingPlayer() : m_dTime(GetTickCount64()), m_dStartTime(GetTickCount64()), m_dFinishTime(GetTickCount64())
{
	m_Type = SKIING_PLAYER;
}

CSkiingPlayer::~CSkiingPlayer()
{
}


void CSkiingPlayer::Initialize(void)
{
	//카메라 추가
	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);
	CCharacter::Initialize();
	//

	//m_tInfo = { 100.f, 200.f, 50.f, 50.f };
	m_vInfo.vPos = { WINCX / 2.f, 100, 0.f };
	m_vInfo.vLook = { 0.f,1.f,0.f };
	m_vInfo.vDir = m_vInfo.vLook;

	m_vPoint.push_back({ -10.f,-5.f,0.f });
	m_vPoint.push_back({ 10.f,-5.f,0.f });
	m_vPoint.push_back({ 10.f,30.f,0.f });
	m_vPoint.push_back({ -10.f,30.f,0.f });

	for (auto& iter : m_vPoint)
	{
		m_vOriginPoint.push_back(iter);
	}
	//플레이어 앵글
	m_fAngle = 0.f;

	//가속
	m_fAccel = 0.2f;
	
	//스피드
	m_fSpeed = 1.5707f;

	//플레이어 사운드 채널
	//CSoundMgr::Get_Instance()->PlaySoundW(L"song_killyourtv.ogg", );
	//m_BGMkey = L"song_killyourtv.ogg";
	m_PlayerSoundCh = 0;

	m_fFrontAngle = 0.f;

	//플레이어 초기상태
	m_State = MOVE;

	InitImage();

	m_iTime = 60;
	m_iStartCount = 5;

	m_iScore = 0;

	//스피드 곱
	m_fSpeedPower = 10.f;

	//점프 사이즈
	m_fJumpSizeX = 1.f;
	m_fJumpSizeY = 1.f;
	m_bJumpEnd = false;

	//예티
	m_bGaugeOn = false;
	m_fGauge = 0;
}

void CSkiingPlayer::Update(void)
{

	//카메라 업데이트
	CCharacter::Update();

	//키값 판단
	Key_Input();

	//상태 업데이트 (애니메이션 전환)
	StateUpdate();


	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vInfo.vPos.x, m_vInfo.vPos.y, 0.f);

	m_vInfo.matWorld = matScale * matRotZ * matTrans;

	//m_SkiingSpeed = m_fAngle * 3;
	//m_fSpeed = m_fSpeed * 3;
	m_SkiingBreak = m_fAngle;

	//브레이크 테스트
	if (m_SkiingBreak < 0)
	{
		m_SkiingBreak *= -1.f;
	}
	//m_fPower = m_vInfo.vDir * (m_fSpeed - m_SkiingBreak) * 5.f;

	if (m_dStartTime + 1000.f < GetTickCount64() &&
		m_iStartCount > 0)
	{
		--m_iStartCount;

		m_dStartTime = GetTickCount64();
	}

	if (m_iStartCount == 0)
	{
		//이동
		D3DXVec3TransformNormal(&m_vInfo.vDir, &m_vInfo.vLook, &m_vInfo.matWorld);
		m_vPower = m_vInfo.vDir * (m_fSpeed - m_SkiingBreak) * m_fSpeedPower;
		m_vInfo.vPos += m_vPower;

		//타이머
		if (m_dTime + 1000.f < GetTickCount64() &&
			m_iTime > 0)
		{
			--m_iTime;
			m_dTime = GetTickCount64();
		}
	}

	//점프사이즈가 최대일때
	if (m_State == JUMP &&
		m_bJumpEnd == false &&
		m_fJumpSizeX >= 5.f &&
		m_fJumpSizeY >= 5.f)
	{
		m_bJumpEnd = true;
	}

	//점프사이즈 다운
	if (m_bJumpEnd)
	{
		m_fJumpSizeX -= 0.1f;
		m_fJumpSizeY -= 0.1f;

		if (m_fJumpSizeX <= 1.f &&
			m_fJumpSizeY <= 1.f)
		{
			m_State = MOVE;
			m_bJumpEnd = false;
		}
	}

	//vPos,vPoint,RECT,Collide,FrontCollide 업데이트
	CObj::UpdatePoint();
	CObj::Update_Rect();

	CObj::Move_Frame();
}

void CSkiingPlayer::LateUpdate(void)
{
}

void CSkiingPlayer::Render(HDC hDC)
{
	if (m_fFrontAngle == 0)
	{
		//m_FrameMap[m_State].iMotion = 0;
	}
	else if (m_fFrontAngle == PI)
	{
		//m_FrameMap[m_State].iMotion = 8;
	}

	TCHAR	szBuff[32] = L"";
	
	swprintf_s(szBuff, L"Time : %d", m_iTime);
	TextOut(hDC, WINCX / 2, 100, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"Score : %d", m_iScore);
	TextOut(hDC, 800, 100, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"StartTime : %d", m_iStartCount);
	TextOut(hDC, 100, 100, szBuff, lstrlen(szBuff));

	//if (g_CollideCheck)
	CObj::CollideRender(hDC);

	if (m_State != JUMP)
	{
		CObj::RotateFrameRender(hDC,D3DXToDegree(m_fAngle));
	}
	if (m_State == JUMP)
	{
		CObj::RotateFrameRender_Size(hDC, D3DXToDegree(m_fAngle), m_fJumpSizeX, m_fJumpSizeY);
	}
	CObj::BasicRender(hDC);
}

void CSkiingPlayer::Release(void)
{
}

void CSkiingPlayer::InitImage() //원하는 만큼 이미지 추가 (프레임은 같은걸 사용)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Images_Sh/skiman-sheet0.png", L"skiman-sheet0"); //플레이어 기본
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Images_Sh/Jump.bmp", L"Jump"); //플레이어 점프
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Images_Sh/yeti-sheet0.bmp", L"Yeti"); //플레이어 예티 충돌
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Images_Sh/Timer.bmp", L"Timer");

	m_OneImgKey = L"Timer";

	FRAME TempFrame;
	TempFrame.AnimKey = L"skiman-sheet0";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 8;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 57;
	TempFrame.iFrameSizeY = 57;

	m_FrameMap.insert({ MOVE, TempFrame });

	TempFrame.AnimKey = L"Jump";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 64;
	TempFrame.iFrameSizeY = 45;

	m_FrameMap.insert({ JUMP, TempFrame });

	TempFrame.AnimKey = L"Yeti";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 0;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 55;
	TempFrame.iFrameSizeY = 82;

	m_FrameMap.insert({ YETI_HIT, TempFrame });

	TempFrame.AnimKey = L"Timer";
	TempFrame.iFrameStart = 0;
	TempFrame.iFrameEnd = 8;
	TempFrame.iMotion = 0;
	TempFrame.dwSpeed = 60;
	TempFrame.dwTime = GetTickCount64();
	TempFrame.iFrameSizeX = 57;
	TempFrame.iFrameSizeY = 57;

	m_FrameMap.insert({ MOVE, TempFrame });

	//CObj* Temp = CObjFactory<CWall>::Create();
	//Temp->SetPos(ML + 120.f, MT + 640 * 0.5f);
	//Temp->AddPoint(-120.f, -640 * 0.5f);
	//Temp->AddPoint(120.f, -640 * 0.5f);
	//Temp->AddPoint(120.f, 640 * 0.5f);
	//Temp->AddPoint(-120.f, 640 * 0.5f);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_NONE, Temp);
}

//stuntguy-sheet0

void CSkiingPlayer::Key_Input(void)
{
	//1.5707f
	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		//m_fAngle -= D3DXToRadian(3.f);
			m_fAngle -= 0.05f;

		if (m_fAngle <= -1.5677f)
		{
			m_fAngle = -1.5707f;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		//m_fAngle += D3DXToRadian(3.f);
		m_fAngle += 0.05f;

		if (m_fAngle >= 1.5677f)
		{
			m_fAngle = 1.5707f;
		}
	}
			


	if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
	{
		D3DXVec3TransformNormal(&m_vInfo.vDir, &m_vInfo.vLook, &m_vInfo.matWorld);
		m_vInfo.vPos += (m_vInfo.vDir * m_fSpeed) * 5.f;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
	{
		D3DXVec3TransformNormal(&m_vInfo.vDir, &m_vInfo.vLook, &m_vInfo.matWorld);
		m_vInfo.vPos -= m_vInfo.vDir * m_fSpeed * 4.f;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		if (m_vPower)
		{
			m_vPower;
		}
		D3DXVec3TransformNormal(&m_vInfo.vDir, &m_vInfo.vLook, &m_vInfo.matWorld);
		m_vInfo.vPos -= m_vInfo.vDir * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('R'))
	{
		m_State = MOVE;
	}

}

/////////////////////////////////////////////////////////////////

//각 객체의 해당 애니메이션 키값 넣어주기 (여기는 상태에 따라 기능이들어가는 곳)
void CSkiingPlayer::StateUpdate()
{
	if (m_PrevState != m_State)
	{
		m_FrameMap[m_State].iFrameStart = 0;
		m_FrameMap[m_State].dwTime = GetTickCount64();
	}

	switch (m_State)
	{
		case DEAD:
		{

			break;
		}
		case IDLE:
		{

			break;
		}
		case MOVE:
		{
			m_fSpeedPower = 10.f;
			break;
		}
		case JUMP:
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"점프.wav", SOUND_PLAYER, 5.f);

			if (!m_bJumpEnd)
			{
				m_fJumpSizeX += 0.1f;
				m_fJumpSizeY += 0.1f;
			}

			break;
		}
		case YETI_HIT:
		{
			m_bGaugeOn = true;
			m_fSpeedPower = 2.f;
			break;
		}
	}

}


void CSkiingPlayer::PlayerPlaySound(TCHAR* _name)
{
	if (m_PlayerSoundCh == 0)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER, SOUND_VOL3);
	else if (m_PlayerSoundCh == 1)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER2, SOUND_VOL3);
	else if (m_PlayerSoundCh == 2)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER3, SOUND_VOL3);
	else if (m_PlayerSoundCh == 3)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER4, SOUND_VOL3);
	else if (m_PlayerSoundCh == 4)
		CSoundMgr::Get_Instance()->PlaySound(_name, SOUND_PLAYER5, SOUND_VOL3);

	++m_PlayerSoundCh;
	if (m_PlayerSoundCh == 5)
		m_PlayerSoundCh = 0;
}

//들어올 때
int CSkiingPlayer::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();

	switch (targetType)
	{
		case SKIING_FLAG:
		{
			if (m_State == JUMP)
			{
				m_iScore += 3;
			}
			if (m_State != JUMP)
			{
				m_iScore += 1;
			}
			break;
		}
		case SKIING_JUMPING_BOARD:
		{
			m_State = JUMP;
			StateUpdate();
			break;
		}
		case SKIING_FINISHLINE:
		{
			
			if (m_iScore >= 10)
			{
				CSceneManager::Get_Instance()->ToNextScene();
				m_dFinishTime = GetTickCount64();
			}

			break;
		}
		case SKIING_SNOWMAN:
		{
			m_State = YETI_HIT;
			break;
		}
	}

	return 0;
}

//나갈 때
int CSkiingPlayer::OutCollision(CObj* _target)
{
	OBJ_TYPE targetType = _target->Get_Type();

	switch (targetType)
	{
		case SKIING_FLAG:
		{

			break;
		}
		case SKIING_JUMPING_BOARD:
		{

			break;
		}
		case SKIING_FINISHLINE:
		{

			break;
		}
		case SKIING_SNOWMAN:
		{
			//m_State = YETI_HIT;
			break;
		}
	}

	return 0;
}

//들어와있는 경우
int CSkiingPlayer::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	OBJ_TYPE targetType = _target->Get_Type();
	m_vInfo.vPos += _dir;

	return 0;
}

