#pragma once
#include "Component.h"
#include "Utilities/InputManager.h"

class InputComponent : public Component
{
public:
	InputComponent() { ComponentTypeID = (uint32_t)DefaultComponentType::InputComponent; };
	virtual ~InputComponent() {};

	virtual void Update(Camera2D* GameCamera, GameObject* Object,
		const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0))override = 0;

	virtual void* Get(uint32_t Message)const override { return nullptr; };
};