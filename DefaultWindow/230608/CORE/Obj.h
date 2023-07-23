#pragma once

#include "Define.h"
#include "Enum.h"
#include "Struct.h"
#include "Functor.h"

class CObj abstract
{
public:
	CObj();
	virtual ~CObj();
	
	//CObj& operator = (const CObj& other);

public:
	virtual void		Initialize(void)		PURE;
	virtual void			Update(void)		PURE;
	virtual void		LateUpdate(void)		PURE;
	virtual void		Render(HDC hDC)			PURE;
	virtual void		Release(void)			PURE;
	virtual void		InitImage()				PURE;

public:
	virtual	int			InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)		PURE;
	virtual	int			OutCollision(CObj* _target)							PURE;
	virtual	int			OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)		PURE;

protected:
	void		Update_Rect();

protected:
	//정보
	OBJ_TYPE		m_Type;
	INFO			m_tInfo;
	vINFO			m_vInfo;


	//다각형 벡터 충돌체
	vector <D3DXVECTOR3>		m_vPoint;
	vector <D3DXVECTOR3>		m_vOriginPoint;
	float			m_fAngle;
	float			m_fMoveAngle;

public :
	void			UpdatePoint();
	vector<D3DXVECTOR3>	GetPoint() { return m_vPoint; }
	void			SetPos(float _x, float _y) { m_vInfo.vPos.x = _x; m_vInfo.vPos.y = _y; }
	float			GetPosX() { return m_vInfo.vPos.x; }
	float			GetPosY() { return m_vInfo.vPos.y; }
	void			AddPoint(float _x, float _y) { m_vPoint.push_back({ _x,_y,0.f }); m_vOriginPoint.push_back({ _x,_y,0.f });}
	void			SetMoveAngle(float _angle) { m_fMoveAngle = _angle; }


protected:
	// 속도, 가속도, Vertical Speed
	float			m_fSpeed;
	float			m_fAccel;
	float			m_fSpeed_Vertical;
	
	//상태, 이전 상태
	OBJ_STATE		m_State;
	OBJ_STATE		m_PrevState;
	
	// 오너 
	CObj*			m_Owner;


public:
	//오너 설정
	void		SetOwner(CObj* _owner) { m_Owner = _owner; }
	CObj*		GetOwner()			   { return m_Owner; }
	
	//속도,가속도 설정
	void		SetAccel(float _accel) { m_fAccel = _accel; }
	void		SetSpeed(float _speed) { m_fSpeed = _speed; }

	//중심점+크기 정보 설정
	INFO*		Get_Info() { return &m_tInfo; }
	vINFO*		Get_vInfo() { return &m_vInfo; }
	//void		Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void		Set_Size(float _fCX, float _fCY) { m_tInfo.fCX = _fCX; m_tInfo.fCY = _fCY; }

	//OBJ 타입 설정
	OBJ_TYPE	Get_Type() { return m_Type; }
	
	//OBJ 상태 설정
	void		Set_State(OBJ_STATE _state) { m_State = _state; }
	OBJ_STATE	Get_State() { return m_State; }
	

	//Anim KEY,Frame 관련
protected:
	//프레임 객체 키
	map<OBJ_STATE,FRAME>	m_FrameMap;
	//단일 프레임 객체 키
	TCHAR* m_OneImgKey;
	bool   m_FrameReverse;

protected:
	void RatioFixByImage(const TCHAR* _tcAnimKey);

	void BasicRender(HDC hDC);
	void FrameRender_Size(HDC hDC, float _RatioX, float _RatioY);
	void RotateFrameRender(HDC hDC, float _angle); 
	void CollideRender(HDC hDC);
	void CollideRender(HDC hDC, RECT _collide);


	void FrameRender(HDC hDC);//
	void RotateRender(HDC hDC, float _angle); //
	void RotateFrameRender_Size(HDC hDC, float _angle, float _resizeX, float _resizeY);//
	
	

	void Move_Frame();



	//FrontAngle,FrontCollide (전방 물체 인식 콜라이더, 바라보는 방향(각))
protected:
	float				m_fFrontAngle;

public:
	void  Set_FrontAngle(float _angle) { m_fFrontAngle = _angle; }
	float Get_FrontAngle() { return m_fFrontAngle; }

	//X 좌표 위치 변경
	void		SetfX(float _fX) { m_tInfo.fX = _fX; }

	
	Gdiplus::Bitmap* CloneBitmap(Gdiplus::Bitmap* sourceBitmap);


public :
	void		Set_FrameStart(OBJSTATE _state, int _frame) { m_FrameMap[_state].iFrameStart = _frame; }

	FRAME*		Get_StateFrame() { return &m_FrameMap[m_State]; }

};

