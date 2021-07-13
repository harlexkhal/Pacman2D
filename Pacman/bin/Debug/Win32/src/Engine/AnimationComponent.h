#pragma once
#include <vector>
#include "Core/Renderer/RendererAPI.h"
#include "Component.h"

class AnimationComponent : public Component
{
public:
	AnimationComponent() { ComponentTypeID = (uint32_t)DefaultComponentType::AnimationComponent; };
	virtual ~AnimationComponent() {};

	virtual void Update(Camera2D* GameCamera, GameObject* Object,
		const std::vector<GameObject*>& WorldObjects = std::vector<GameObject*>(0)) {};
	virtual void* Get(uint32_t Message)const override { return nullptr; };

	float Animation_TimeFrame = 0;

	void PushBack_WalkSprite_Animation(Texture* Tex);
	void PushBack_RunSprite_Animation(Texture* Tex);
	void PushBack_StandSprite_Animation(Texture* Tex);
	void PushBack_AttackSprite_Animation(Texture* Tex);
	void PushBack_JumpSprite_Animation(Texture* Tex);

protected:
	std::vector<Texture*> WalkSprite_Animation;
	std::vector<Texture*> RunSprite_Animation;
	std::vector<Texture*> StandSprite_Animation;
	std::vector<Texture*> AttackSprite_Animation;
	std::vector<Texture*> JumpSprite_Animation;

	std::vector<Texture*>::iterator Anime_Iterator;
};