#pragma once
#include "Engine/GameObject.h"
#include "Engine/PhysicsComponent.h"

class LandPhysics : public PhysicsComponent
{
public:
	LandPhysics(){};
	virtual ~LandPhysics() {};

	virtual void Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0))override;
	void* Get(uint32_t Message)const;

private:
	Esm::AABB Volume;
};