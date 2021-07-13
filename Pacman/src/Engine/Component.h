#pragma once
#include <vector>
#include "Utilities/TimeSteps.h"
#include "Utilities/Camera2D.h"

enum class DefaultComponentType
{
	GraphicsComponent = 0,
	InputComponent,
	PhysicsComponent,
	ParticlePhysicsGeneratorComponent,
	AnimationComponent,
	TargetIntegratorComponent
};

enum class BroadCastMessage
{
	BoundingVolume = 0,
	ObjectOnGround,
	CollidedObjectsList,
	ActiveTargetIntegrator
};

class GameObject;
class Component
{
public:
	Component() {};
	virtual ~Component() {};

	virtual void Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0)) = 0;

	virtual void* Get(uint32_t Message)const = 0;
	uint32_t ComponentTypeID;
};