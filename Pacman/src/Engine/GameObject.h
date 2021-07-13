#pragma once
#include <vector>
#include <map>
#include <Esmath/Esmath.h>
#include "Core/Renderer/RendererAPI.h"
#include "Component.h"
#include "GraphicsComponent.h"

class GameObject
{
public:
	GameObject(GraphicsComponent* Graphics = nullptr, Component* Input = nullptr, Component* Animation = nullptr);
	virtual ~GameObject();

	virtual void Update(Camera2D* GameCamera, const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0));
	virtual void Render(Camera2D* GameCamera, const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0));

	/*Never by any means push a Graphics Component into a Game's Object Component bucket---
	if you ever need a Graphics in a GameObject, it Should be initialized from the GameObject Constructor*/
	virtual void PushComponent(Component* NewObjectComponent);
	virtual void PushBackComponent(Component* NewObjectComponent);
	virtual void RemoveComponent();

	//TODO:: Create Setter and Getter Functions for these member variables
	Esm::Vec3 Size, Color, Position, Velocity;
	Esm::Vec4 Rotate;
	Texture* DefaultTexture;
	float mass;
	uint32_t ClassID;
	uint32_t ID;
	
	std::vector <Component*> Components;
	GraphicsComponent* m_Graphics;

private:
	int m_ContainerComponentIndex__ = 0;
};