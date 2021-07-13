#include "GameObject.h"

GameObject::GameObject(GraphicsComponent* Graphics, Component* Input, Component* Animation)
{
	if (Graphics != nullptr)
		m_Graphics = Graphics;

	if (Input != nullptr)
		Components.emplace(Components.begin() + (m_ContainerComponentIndex__++), Input);

	if (Animation != nullptr)
		Components.emplace(Components.begin() + (m_ContainerComponentIndex__++), Animation);

	Rotate = Esm::Vec4(0, 0, 1, Esm::Radian(0));
}

GameObject::~GameObject()
{
	delete m_Graphics;
	for (auto It : Components)
		 delete It;
	Components.clear();
}

void GameObject::Update(Camera2D* GameCamera, const std::vector<GameObject*>& WorldObjects)
{
	if(!Components.empty())
	for (auto It : Components)
		It->Update(GameCamera, this, WorldObjects);	
}

void GameObject::Render(Camera2D* GameCamera, const std::vector<GameObject*>& WorldObjects)
{
	/*---Only Updates Entities/Gameobjects that has a Graphics Component in them---*/
	if (this->m_Graphics)
		m_Graphics->Update(GameCamera, this);
}

void GameObject::PushComponent(Component* NewObjectComponent)
{
	Components.emplace(Components.begin() + (m_ContainerComponentIndex__++), NewObjectComponent);
}

void GameObject::PushBackComponent(Component* NewObjectComponent)
{
	Components.emplace_back(NewObjectComponent);
}

void GameObject::RemoveComponent()
{
}