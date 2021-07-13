#include "Engine/Utilities/TimeSteps.h"
#include "NPCAnimation.h"

void NPCAnimation::Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects)
{
	float ElapsedTime = 0.03f;
	if (Animation_TimeFrame >= ElapsedTime)
	{
		++Anime_Iterator;

		if (Anime_Iterator != WalkSprite_Animation.end())
			Object->DefaultTexture = *Anime_Iterator;

		Animation_TimeFrame = 0;
	}

	Animation_TimeFrame += std::abs(Object->Velocity.x) * TimeSteps::GetTimeSteps();

	if (Anime_Iterator == WalkSprite_Animation.end())
		Anime_Iterator = WalkSprite_Animation.begin();
}