#pragma once
#include "Engine/GameObject.h"
#include "Engine/ParticlePhysicsGeneratorComponent.h"

class FlameParticle : public Particle
{
public:
	FlameParticle(Esm::Vec3 Color)
	{
		this->Color = Color;
		this->Size = Esm::Vec3(0.01f, 0.01f, 0.0f);
		Box = Esm::AABB(Position - Size, Position + Size);
	};
};

//-----------------------Flame Particle Physics Generator------------------------------------------------------------
class FlamePhysicsParticleGenerator : public ParticlePhysicsGenerator
{
public:
	FlamePhysicsParticleGenerator(Renderer* ParticleSprite, Esm::Vec3 Color = Esm::Vec3(1.0f, 0.5f, 0.2f));
	virtual ~FlamePhysicsParticleGenerator();

	virtual void Update(Camera2D* GameCamera, GameObject* Object,
		const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0));

	virtual void* Get(uint32_t Message)const override { return nullptr; };

	void SpawnParticle(Particle& Atom);
};