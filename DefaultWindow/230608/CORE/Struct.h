#pragma once

struct fPOINT
{
	float x;
	float y;
	fPOINT() {}
	fPOINT(float x, float y) :x(x), y(y) {}
};

//����, ����, ���� ����
typedef struct tagInfo
{
	float	fX;				// ���� X
	float	fY;				// ���� Y
	float	fCX;			// ���� ����
	float	fCY;			// ���� ����

	float	fPrevX = 0.f;	// ���� X
	float	fPrevY = 0.f;	// ���� Y
	float	fRatioX = 1.f;	// ���� X
	float	fRatioY = 1.f;	// ���� Y
}INFO, POINT_RECT;

typedef struct vtagInfo
{
	D3DXVECTOR3		vPos;

	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;

	//D3DXVECTOR3		vNormal;

	D3DXMATRIX		matWorld;

}vINFO;

/******************************LINE******************************/
// Line�� float Point
typedef	struct tagLinePoint
{
	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

	float	fX;
	float	fY;

}LINEPOINT;

//Line ����ü (���� ��, ������ ��)
typedef struct tagLine
{
	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLpoint, LINEPOINT& _tRpoint)
		: tLpoint(_tLpoint), tRpoint(_tRpoint) { }

	LINEPOINT	tLpoint;
	LINEPOINT	tRpoint;

}LINE;


/******************************Frame******************************/
typedef struct tagFrame
{
	TCHAR*		AnimKey;
	int			iFrameStart;
	int			iFrameEnd;
	int			iMotion; //���� ��

	int			iFrameSizeX;
	int			iFrameSizeY;

	DWORD		dwSpeed;
	DWORD		dwTime;

}FRAME;

typedef struct tagUI
{
	TCHAR*	AnimKey;
	int		PosX;
	int		PosY;
	int		SizeX;
	int		SizeY;
	bool	bCheckOn;
}UI;