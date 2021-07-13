#pragma once
#include "Engine/GameObject.h"
#include "Engine/PhysicsComponent.h"

class BallPhysics : public PhysicsComponent
{
public:
	BallPhysics() {};
	BallPhysics(Esm::Vec3 WorldPosition, Esm::Vec3 HalfSize)
	{
		Volume = Esm::AABB(WorldPosition - HalfSize, WorldPosition + HalfSize);
	};
	virtual ~BallPhysics() {};

	virtual void Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0))override;
	virtual void* Get(uint32_t Message)const override;

private:
	Esm::AABB Volume;
};