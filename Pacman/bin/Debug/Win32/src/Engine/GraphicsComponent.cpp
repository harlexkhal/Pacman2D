#include "GameObject.h"
#include "ParticlePhysicsGeneratorComponent.h"
#include "TargetIntegratorComponent.h"

#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(Renderer* SpriteQuad)
{
	this->SpriteQuad = SpriteQuad;
	ComponentTypeID = (uint32_t)DefaultComponentType::GraphicsComponent;
}

void GraphicsComponent::Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects)
{
	Esm::Mat4x4 Transform(1.0f);
	Transform.Rotate(Esm::Vec3(Object->Rotate.x, Object->Rotate.y, Object->Rotate.z), Object->Rotate.a);
	Transform.Translate(Object->Position);
	Transform.Scale(Object->Size);
	Esm::Vec4 rgbaColor(Object->Color.x, Object->Color.y, Object->Color.z, 1.0f);

	SpriteQuad->OnRender(GameCamera, Object->DefaultTexture, Transform, rgbaColor);
}

void GraphicsComponent::Update(Camera2D* GameCamera, Particle* Atom)
{
	Esm::Vec4 rgbaColor(Atom->Color.x, Atom->Color.y, Atom->Color.z, Atom->aColorIntensity);
	SpriteQuad->OnRender(GameCamera, Atom->m_Texure__, Atom->Position, Atom->Size, rgbaColor);
}

void GraphicsComponent::Update(Camera2D* GameCamera, TraceObject* Object)
{
	Esm::Vec4 rgbaColor(Object->Color.x, Object->Color.y, Object->Color.z, 1.0f);
	SpriteQuad->OnRender(GameCamera, Object->m_Texure__, Object->Position, Object->Size, rgbaColor);
}