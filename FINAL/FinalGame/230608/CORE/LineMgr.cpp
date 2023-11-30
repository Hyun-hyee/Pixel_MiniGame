#include "stdafx.h"
#include "LineMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
	{
		iter->Render(hDC);
	}
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

void CLineMgr::Add_Line(LINEPOINT _Lpoint, LINEPOINT _Rpoint)
{
	_Lpoint.fY -= 25.f;
	_Rpoint.fY -= 25.f;
	m_LineList.push_back(new CLine(_Lpoint, _Rpoint));
}

bool CLineMgr::CollisionLine(INFO& _rInfo, float* _pY)
{
	if (m_LineList.empty())
		return false;

	list<CLine*>		TargetList;
	CLine* pTarget = nullptr;
	// ���� �Ʒ��� �ִ� ���� ���� ���� ����
	float	fBottomY = -INFINITY;
	float	fHeight = 0.f;// _rInfo.fCY * 0.5f;

	// Ư�� ������ x�� ���̿� �ִ� ������ ã��
	for (auto& line : m_LineList)
	{
		if (line->Get_Info().tLpoint.fX <= _rInfo.fX && line->Get_Info().tRpoint.fX > _rInfo.fX ||
			line->Get_Info().tRpoint.fX <= _rInfo.fX && line->Get_Info().tLpoint.fX > _rInfo.fX)
		{
			TargetList.push_back(line);

			// ���⼭ fBaseH�� �ʱ� ���̸� ���� ũ�� �����ϱ���������
			// �߽���ǥ �ٷ� �Ʒ��� ���� ���� ����� �ƴ�.
			if (fBottomY < line->Get_Info().tLpoint.fY - fHeight)
			{
				fBottomY = line->Get_Info().tLpoint.fY - fHeight;
				pTarget = line;
			}

			if (fBottomY < line->Get_Info().tRpoint.fY - fHeight)
			{
				fBottomY = line->Get_Info().tRpoint.fY - fHeight;
				pTarget = line;
			}
		}
	}

	// �Ʒ��� �ش��ϴ� ������ ������ ����Ʈ�� üũ�Ѵ�.
	if (TargetList.empty())
		return false;

	// ���� ����Ʈ �߿��� ���� ����� ������ ã�� �ɷ�����.
	for (auto& line : TargetList)
	{
		float	x1 = line->Get_Info().tLpoint.fX;
		float	x2 = line->Get_Info().tRpoint.fX;

		float	y1 = line->Get_Info().tLpoint.fY - fHeight;
		float	y2 = line->Get_Info().tRpoint.fY - fHeight;

		float	fTargetY = ((y2 - y1) / (x2 - x1)) * (_rInfo.fX - x1) + y1;
		float	fPrevTargetY = ((y2 - y1) / (x2 - x1)) * (_rInfo.fPrevX - x1) + y1;

		// �ɷ����� �ڵ�
		if (fTargetY <= fBottomY && fTargetY >= _rInfo.fY)
		{
			fBottomY = fTargetY;

			pTarget = line;
		}

		else if (fPrevTargetY <= fBottomY && fPrevTargetY > fTargetY &&
			(_rInfo.fY > y1 && _rInfo.fY < y2) || (_rInfo.fY > y2 && _rInfo.fY < y1))
		{
			fBottomY = fTargetY;

			pTarget = line;
		}
	}

	if (!pTarget)
		return false;


	//�߰�) Ÿ�� ������ ĳ���� ���̿� ���̰� ũ�� false
	//if (abs(pTarget->Get_Info().tLpoint.fY - _rInfo.fY) > _rInfo.fCY)
	//	return false;


	float	x1 = pTarget->Get_Info().tLpoint.fX;
	float	x2 = pTarget->Get_Info().tRpoint.fX;

	float	y1 = pTarget->Get_Info().tLpoint.fY - fHeight;
	float	y2 = pTarget->Get_Info().tRpoint.fY - fHeight;

	// ���� * ��ȯ�� �ʺ� + ���� ���� y��
	*_pY = ((y2 - y1) / (x2 - x1)) * (_rInfo.fX - x1) + y1;

	return true;
}

void CLineMgr::Change_Scene()
{
	Release();
}
