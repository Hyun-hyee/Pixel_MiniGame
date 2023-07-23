#pragma once
#include "stdafx.h"
#include "Define.h"
#include "Enum.h"
#include "Struct.h"
#include "Functor.h"

class CObj;

class CCollisionMgr
{
private:
	CCollisionMgr();
	~CCollisionMgr();

private:
	static CCollisionMgr* m_pInstance;

public:
	static CCollisionMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCollisionMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void Initialize();
	void Update(list<CObj*> _firstList, list<CObj*> _secondList);
	void Release();

	 DIR Collision_Enter_SS(RECT* _first, RECT* _second);
	 bool PolygonCollision(const std::vector<D3DXVECTOR3>& polygon1, const std::vector<D3DXVECTOR3>& polygon2, D3DXVECTOR3& collisionNormal, float& collisionAngle);
	 bool AxisOverlap(const std::vector<D3DXVECTOR3>&polygon1, const std::vector<D3DXVECTOR3>&polygon2, const D3DXVECTOR3 & axis, float& minOverlap);


private:
	vector<pair<CObj*, CObj*>> m_CollisionOutMap;

};

