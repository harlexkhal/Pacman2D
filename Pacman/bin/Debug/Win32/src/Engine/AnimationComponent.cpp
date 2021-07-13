#include "AnimationComponent.h"

void AnimationComponent::PushBack_WalkSprite_Animation(Texture* Tex)
{
	WalkSprite_Animation.emplace_back(Tex);
	Anime_Iterator = WalkSprite_Animation.begin();
}

void AnimationComponent::PushBack_RunSprite_Animation(Texture* Tex)
{
	RunSprite_Animation.emplace_back(Tex);
	Anime_Iterator = RunSprite_Animation.begin();
}

void AnimationComponent::PushBack_StandSprite_Animation(Texture* Tex)
{
	StandSprite_Animation.emplace_back(Tex);
	Anime_Iterator = StandSprite_Animation.begin();
}

void AnimationComponent::PushBack_AttackSprite_Animation(Texture* Tex)
{
	AttackSprite_Animation.emplace_back(Tex);
	Anime_Iterator = AttackSprite_Animation.begin();
}

void AnimationComponent::PushBack_JumpSprite_Animation(Texture* Tex)
{
	JumpSprite_Animation.emplace_back(Tex);
	Anime_Iterator = JumpSprite_Animation.begin();
}