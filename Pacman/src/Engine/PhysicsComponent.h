#pragma once
#include "Component.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent() { ComponentTypeID = (uint32_t)DefaultComponentType::PhysicsComponent; };
	virtual ~PhysicsComponent() {};

	virtual void Update(Camera2D* GameCamera, GameObject* Object,
		const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0))override = 0;

	virtual void LinearCollisionResponse(GameObject* OwnedObject, GameObject* WorldObject);
	
	virtual void* Get(uint32_t Message)const override { return nullptr; };

protected:
	std::vector<GameObject*> CollidedObjectList;
	float Const_G_Acceleration = 9.8f;
	float Cr; //---Coefficient Of Restitution Constant for CollisionResponse between 2 RigidBodies---
};