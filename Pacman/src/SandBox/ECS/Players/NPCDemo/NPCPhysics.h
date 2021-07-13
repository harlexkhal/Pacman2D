#pragma once

#include "Engine/GameObject.h"
#include "Engine/PhysicsComponent.h"

class NPCPhysics : public PhysicsComponent
{
public:
	NPCPhysics() {};
	virtual ~NPCPhysics() {};

	virtual void Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0))override;
	virtual void* Get(uint32_t Message)const override;

private:
	Esm::AABB Volume;
};