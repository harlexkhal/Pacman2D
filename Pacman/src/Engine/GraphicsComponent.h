#pragma once
#include "Core/Renderer/RendererAPI.h"
#include "Component.h"
#include "Utilities/InputManager.h"

class Particle;
class TraceObject;
class GraphicsComponent : public Component
{
public:
	GraphicsComponent(Renderer* SpriteQuad);
	virtual ~GraphicsComponent() {};

	virtual void Update(Camera2D* GameCamera, GameObject* Object,
		const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0))override;

	void Update(Camera2D* GameCamera, Particle* Atom);
	void Update(Camera2D* GameCamera, TraceObject* Atom);

	virtual void* Get(uint32_t Message)const override { return nullptr; };

protected:
	Renderer* SpriteQuad;
};