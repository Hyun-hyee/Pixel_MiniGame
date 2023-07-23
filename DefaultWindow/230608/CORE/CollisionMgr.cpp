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
					//�浹 IN �߾����� ���� üũ
					auto Searchiter = find(m_CollisionOutMap.begin(), m_CollisionOutMap.end(), SearchPair);
					float test = D3DXToDegree(vAngle);
					//OnCollision �̺�Ʈ
					if (Searchiter == m_CollisionOutMap.end())
					{
						//InCollision �̺�Ʈ
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
						//OutCollision �̺�Ʈ
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



// �ٰ��� �浹 ���� �Լ�
bool CCollisionMgr::PolygonCollision(const std::vector<D3DXVECTOR3>& polygon1, const std::vector<D3DXVECTOR3>& polygon2, D3DXVECTOR3& collisionNormal, float& collisionAngle) {
	  int numVertices1 = polygon1.size();
    int numVertices2 = polygon2.size();

    // �浹 �ּ� ������ �ʱ�ȭ
    float minOverlap = std::numeric_limits<float>::infinity();
    D3DXVECTOR3 minOverlapAxis;
    int collisionEdgeIndex1 = -1;
    int collisionEdgeIndex2 = -1;

    for (int i = 0; i < numVertices1; ++i) {
        // �ٰ����� �� ���� ���� �� ���
        D3DXVECTOR3 edge = polygon1[(i + 1) % numVertices1] - polygon1[i];
        D3DXVECTOR3 axis = { -edge.y, edge.x, 0.0f }; // 2D �浹�̹Ƿ� z���� 0���� ����

        // �ٰ��� �� ����ȭ
        D3DXVec3Normalize(&axis, &axis);

        // �浹 �˻縦 ���� ���� �Լ� ȣ��
        float overlap;
        if (!AxisOverlap(polygon1, polygon2, axis, overlap)) {
            return false; // �浹���� ����
        }

        // �ּ� ��ø�� ����
        if (overlap < minOverlap) {
            minOverlap = overlap;
            minOverlapAxis = axis;
            collisionEdgeIndex1 = i;
            collisionEdgeIndex2 = -1;
        }
    }

    for (int i = 0; i < numVertices2; ++i) {
        // �ٰ��� 2�� �� ���� ���� �� ���
        D3DXVECTOR3 edge = polygon2[(i + 1) % numVertices2] - polygon2[i];
        D3DXVECTOR3 axis = { -edge.y, edge.x, 0.0f }; // 2D �浹�̹Ƿ� z���� 0���� ����

        // �ٰ��� �� ����ȭ
        D3DXVec3Normalize(&axis, &axis);

        // �浹 �˻縦 ���� ���� �Լ� ȣ��
        float overlap;
        if (!AxisOverlap(polygon2, polygon1, axis, overlap)) {
            return false; // �浹���� ����
        }

        // �ּ� ��ø�� ����
        if (overlap < minOverlap) {
            minOverlap = overlap;
            minOverlapAxis = axis;
            collisionEdgeIndex1 = -1;
            collisionEdgeIndex2 = i;
        }
    }

    // �浹�ϴ� ���, �浹 ����(normal ����)�� ȸ�� ���� ��ȯ
    collisionNormal = minOverlapAxis;

    
    // �� ���� ������ ȸ�� �� ���
	D3DXVECTOR3 axisX = { 1.f,0.f,0.f };
	collisionAngle = acosf(D3DXVec3Dot(&collisionNormal, &axisX));

	if (collisionNormal.y > 0.f)
		collisionAngle += D3DX_PI / 2.f;
	return true;
}

// �ٰ��� ȸ�� �浹 �˻縦 ���� ���� �Լ�
bool CCollisionMgr::AxisOverlap(const std::vector<D3DXVECTOR3>& polygon1, const std::vector<D3DXVECTOR3>& polygon2, const D3DXVECTOR3& axis, float& minOverlap) {
	float min1 = D3DXVec3Dot(&axis, &polygon1[0]);
	float max1 = min1;

	// �ٰ��� 1�� �ּ�, �ִ� ������ ���
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

	// �ٰ��� 2�� �ּ�, �ִ� ������ ���
	for (int i = 1; i < polygon2.size(); ++i) {
		float projection = D3DXVec3Dot(&axis, &polygon2[i]);
		if (projection <= min2) {
			min2 = projection;
		}
		else if (projection >= max2) {
			max2 = projection;
		}
	}

	// �浹�� ���� ���
	if (min1 > max2 || min2 > max1) {
		return false;
	}

	// �浹�� �ִ� ���, ��ø�� ���� ���
	if (min1 < min2) {
		minOverlap = min2 - max1;
	}
	else {
		minOverlap = min1 - max2;
	}

	return true; // �浹��
}