#pragma once
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

class TraceObject
{
public:
	TraceObject(Texture* Tex, Esm::Vec3 Color)
		:m_Texure__(Tex), Color(Color) {};

	Esm::Vec3 Position;
	Esm::Vec3 Velocity;
	Esm::Vec3 Color;
	Texture* m_Texure__;
	Esm::Vec3 Size = Esm::Vec3(0.01f, 0.01f, 0.0f);
	float aColorIntensity = 1.0f;
};

class TargetIntegratorComponent : public Component
{
public:
	TargetIntegratorComponent(Renderer* ParticleSprite, Texture* Tex, Esm::Vec3 Color = Esm::Vec3(0.0f,0.0f,0.0f));
	virtual ~TargetIntegratorComponent();

	virtual void Update(Camera2D* GameCamera, GameObject* Object,
		const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0));

	virtual void* Get(uint32_t Message)const override { return nullptr; };

protected:
	GraphicsComponent* ObjectRenderer;
	TraceObject* TrackObject;

	std::vector<Esm::Vec3> Positions;

	float Stored_Rotation;
	Esm::Vec3 Stored_Velocity;
	Esm::Vec3 Stored_src_Position;

	const float Const_G_Acceleration = 9.8f;
};