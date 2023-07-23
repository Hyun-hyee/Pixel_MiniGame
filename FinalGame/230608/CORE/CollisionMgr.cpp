#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"

CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Initialize()
{
}

void CCollisionMgr::Update(list<CObj*> _firstList, list<CObj*> _secondList)
{
	//DIR CollisionDIR = DIR_NONE;
	int ObjEvent = OBJ_NOEVENT;
	D3DXVECTOR3 vDIR;
	float		vAngle;

	for (auto& iter : _firstList)
	{

		for (auto& iter2 : _secondList)
		{
			vDIR = { 0.f,0.f,0.f };

			if (iter != iter2)
			{
					PolygonCollision(iter->GetPoint(), iter2->GetPoint(), vDIR, vAngle);
					//CollisionDIR = Collision_Enter_SS(iter->Get_Collide(), iter2->Get_Collide());
				
				pair<CObj*, CObj*> SearchPair(iter, iter2);

				if (!(vDIR.x == 0.f && vDIR.y == 0.f && vDIR.z == 0.f))
				{
					//충돌 IN 했었는지 여부 체크
					auto Searchiter = find(m_CollisionOutMap.begin(), m_CollisionOutMap.end(), SearchPair);
					float test = D3DXToDegree(vAngle);
					//OnCollision 이벤트
					if (Searchiter == m_CollisionOutMap.end())
					{
						//InCollision 이벤트
						m_CollisionOutMap.push_back({ iter,iter2 });
						ObjEvent = (iter)->InCollision((iter2), vDIR, vAngle);
					}
					ObjEvent = (iter)->OnCollision((iter2), vDIR, vAngle);
					
				}
				else
				{
					auto Searchiter = find(m_CollisionOutMap.begin(), m_CollisionOutMap.end(), SearchPair);

					if (Searchiter != m_CollisionOutMap.end())
					{
						//OutCollision 이벤트
						(iter)->OutCollision((iter2));
						m_CollisionOutMap.erase(Searchiter);
					}
				}
					
				switch (ObjEvent)
				{
				case OBJ_NOEVENT:
					break;
				}
				ObjEvent = OBJ_NOEVENT;
			}
		}
	}
}

void CCollisionMgr::Release()
{
}

DIR CCollisionMgr::Collision_Enter_SS(RECT* _first, RECT* _second)
{
	RECT section;
	if (IntersectRect(&section, _first, _second))
	{
		if (section.right == _second->right)
			return LEFT;
		else if (section.left == _second->left)
			return RIGHT;
		else if (section.top == _second->top)
			return BOTTOM;
		else if (section.bottom == _second->bottom)
			return TOP;
	}
	
	return DIR_NONE;

}



// 다각형 충돌 감지 함수
bool CCollisionMgr::PolygonCollision(const std::vector<D3DXVECTOR3>& polygon1, const std::vector<D3DXVECTOR3>& polygon2, D3DXVECTOR3& collisionNormal, float& collisionAngle) {
	  int numVertices1 = polygon1.size();
    int numVertices2 = polygon2.size();

    // 충돌 최소 투영값 초기화
    float minOverlap = std::numeric_limits<float>::infinity();
    D3DXVECTOR3 minOverlapAxis;
    int collisionEdgeIndex1 = -1;
    int collisionEdgeIndex2 = -1;

    for (int i = 0; i < numVertices1; ++i) {
        // 다각형의 각 변에 대한 축 계산
        D3DXVECTOR3 edge = polygon1[(i + 1) % numVertices1] - polygon1[i];
        D3DXVECTOR3 axis = { -edge.y, edge.x, 0.0f }; // 2D 충돌이므로 z축은 0으로 설정

        // 다각형 축 정규화
        D3DXVec3Normalize(&axis, &axis);

        // 충돌 검사를 위한 헬퍼 함수 호출
        float overlap;
        if (!AxisOverlap(polygon1, polygon2, axis, overlap)) {
            return false; // 충돌하지 않음
        }

        // 최소 중첩값 갱신
        if (overlap < minOverlap) {
            minOverlap = overlap;
            minOverlapAxis = axis;
            collisionEdgeIndex1 = i;
            collisionEdgeIndex2 = -1;
        }
    }

    for (int i = 0; i < numVertices2; ++i) {
        // 다각형 2의 각 변에 대한 축 계산
        D3DXVECTOR3 edge = polygon2[(i + 1) % numVertices2] - polygon2[i];
        D3DXVECTOR3 axis = { -edge.y, edge.x, 0.0f }; // 2D 충돌이므로 z축은 0으로 설정

        // 다각형 축 정규화
        D3DXVec3Normalize(&axis, &axis);

        // 충돌 검사를 위한 헬퍼 함수 호출
        float overlap;
        if (!AxisOverlap(polygon2, polygon1, axis, overlap)) {
            return false; // 충돌하지 않음
        }

        // 최소 중첩값 갱신
        if (overlap < minOverlap) {
            minOverlap = overlap;
            minOverlapAxis = axis;
            collisionEdgeIndex1 = -1;
            collisionEdgeIndex2 = i;
        }
    }

    // 충돌하는 경우, 충돌 방향(normal 벡터)과 회전 각을 반환
    collisionNormal = minOverlapAxis;

    
    // 두 벡터 사이의 회전 각 계산
	D3DXVECTOR3 axisX = { 1.f,0.f,0.f };
	collisionAngle = acosf(D3DXVec3Dot(&collisionNormal, &axisX));

	if (collisionNormal.y > 0.f)
		collisionAngle += D3DX_PI / 2.f;
	return true;
}

// 다각형 회전 충돌 검사를 위한 헬퍼 함수
bool CCollisionMgr::AxisOverlap(const std::vector<D3DXVECTOR3>& polygon1, const std::vector<D3DXVECTOR3>& polygon2, const D3DXVECTOR3& axis, float& minOverlap) {
	float min1 = D3DXVec3Dot(&axis, &polygon1[0]);
	float max1 = min1;

	// 다각형 1의 최소, 최대 투영값 계산
	for (int i = 1; i < polygon1.size(); ++i) {
		float projection = D3DXVec3Dot(&axis, &polygon1[i]);
		if (projection <= min1) {
			min1 = projection;
		}
		else if (projection >= max1) {
			max1 = projection;
		}
	}

	float min2 = D3DXVec3Dot(&axis, &polygon2[0]);
	float max2 = min2;

	// 다각형 2의 최소, 최대 투영값 계산
	for (int i = 1; i < polygon2.size(); ++i) {
		float projection = D3DXVec3Dot(&axis, &polygon2[i]);
		if (projection <= min2) {
			min2 = projection;
		}
		else if (projection >= max2) {
			max2 = projection;
		}
	}

	// 충돌이 없는 경우
	if (min1 > max2 || min2 > max1) {
		return false;
	}

	// 충돌이 있는 경우, 중첩된 영역 계산
	if (min1 < min2) {
		minOverlap = min2 - max1;
	}
	else {
		minOverlap = min1 - max2;
	}

	return true; // 충돌함
}