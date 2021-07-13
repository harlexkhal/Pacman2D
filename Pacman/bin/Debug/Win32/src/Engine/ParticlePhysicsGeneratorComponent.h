#pragma once
#include <Esmath/Esmath.h>
#include "Core/Renderer/RendererAPI.h"
#include "Component.h"
#include "GraphicsComponent.h"
#include "Utilities/TimeSteps.h"

class Particle
{
public:
	Particle() {};
	
	Esm::Vec3 Position;
	Esm::Vec3 Velocity;
	Esm::Vec3 Color;
	Esm::Vec3 Size;
	Texture* m_Texure__;
	float aColorIntensity = 1.0f;
	float LifeSpan = 0.0f;

	//just AABB provided for now to add other Bounding volumes like Sphere, Triangles, etc--
	Esm::AABB Box;
};

class ParticlePhysicsGenerator : public Component 
{
public:
	ParticlePhysicsGenerator() {};
	virtual ~ParticlePhysicsGenerator() {};
	
	virtual void Update(Camera2D* GameCamera, GameObject* Object,
		const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0))override = 0;

	virtual void* Get(uint32_t Message)const override { return nullptr; };

protected:
	unsigned int m_NumberOfParticles__;
	unsigned int m_SpawnRate;
	GraphicsComponent* ParticleGraphics;
	std::vector<Particle*> Particles;
	std::vector<Particle*>::iterator LastParticle_It;

	Esm::Vec3 m_Position;
	Esm::Vec3 m_Size;
	Esm::Vec3 Color;
};