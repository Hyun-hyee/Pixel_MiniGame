#include "stdafx.h"
#include "Character.h"
#include "Component.h"


CCharacter::CCharacter() :
	m_bJump(false), m_fJump_Power(0.f), m_fJump_Angle(0.f)
	, m_iAdditionJump_MaxCount(0), m_iAdditionJump_Count(0), m_TimeStop_HurtCount(1.f)
	, m_TimeStop_HurtOn(false)
{
	for (int i = 0; i < DIR_END; ++i)
		m_DirCheck[i] = false;
}

CCharacter::~CCharacter()
{
	for (Component* component : _components)
	{
		delete component;
		component = nullptr;
	}
}

void CCharacter::Initialize()
{
	for (Component* component : _components)
	{
		component->Initialize();
	}
}

void CCharacter::Update()
{
	for (Component* component : _components)
	{
		component->Update();
	}
}

void CCharacter::LateUpdate(void)
{
}

void CCharacter::Render(HDC hdc)
{
	for (Component* component : _components)
	{
		component->Render(hdc);
	}
}

void CCharacter::Release(void)
{

}

int CCharacter::InCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}

int CCharacter::OutCollision(CObj* _target)
{
	return 0;
}

int CCharacter::OnCollision(CObj* _target, D3DXVECTOR3 _dir, float _Angle)
{
	return 0;
}

void CCharacter::AddComponent(Component* component)
{
	if (component == nullptr)
		return;

	component->SetOwner(this);
	_components.push_back(component);
}

void CCharacter::RemoveComponent(Component* component)
{
	auto findIt = std::find(_components.begin(), _components.end(), component);
	if (findIt == _components.end())
		return;

	_components.erase(findIt);
}



