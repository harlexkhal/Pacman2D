#pragma once
#include "Engine/GameObject.h"
#include "Engine/InputComponent.h"

class Cannon_Input : public InputComponent
{
public:
	Cannon_Input() {};
	virtual ~Cannon_Input() {};

	virtual void Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0))override;
	virtual void* Get(uint32_t Message)const override;

protected:
	bool ActivateTracer;
};