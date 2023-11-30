#include "stdafx.h"
#include "CameraComponent.h"
#include "Character.h"
#include "SceneManager.h"
#include "KeyMgr.h"

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Initialize()
{
}

void CameraComponent::Update()
{
	if (_owner == nullptr)
		return;

	BackSize = CSceneManager::Get_Instance()->Get_BackSize();

		//오너 위치 저장
		pos = { _owner->Get_Info()->fX, _owner->Get_Info()->fY };



	//카메라 배경 범위 제한
	if (pos.x <= ML + MCX / 2.f)
		pos.x = ML + MCX / 2.f;
	else if (pos.x >= BackSize.x - (MCX / 2.f))
		pos.x = BackSize.x - (MCX / 2.f);

	if (pos.y <= MT + MCY / 2.f)
		pos.y = MT + MCY / 2.f;
	else if (pos.y >= BackSize.y - (MCY / 2.f))
		pos.y = BackSize.y -(MCY / 2.f);

	CSceneManager::Get_Instance()->SetCameraPos(pos);

}

void CameraComponent::Render(HDC hdc)
{
}
