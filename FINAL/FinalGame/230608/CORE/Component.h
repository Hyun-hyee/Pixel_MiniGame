#pragma once

#include "Define.h"
#include "Enum.h"
#include "Struct.h"
#include "Functor.h"

class CCharacter;

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render(HDC hdc) { }

	void SetOwner(CCharacter* owner) { _owner = owner; }
	CCharacter* GetOwner() { return _owner; }

protected:
	CCharacter* _owner;
};

