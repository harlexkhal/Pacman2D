#pragma once
#include "Engine/GameObject.h"
#include "Engine/AnimationComponent.h"

class NPCAnimation : public  AnimationComponent
{
public:
	NPCAnimation() {};
	virtual ~NPCAnimation() {};

	virtual void Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0))override;
	virtual void* Get(uint32_t Message)const override { return nullptr; };
};