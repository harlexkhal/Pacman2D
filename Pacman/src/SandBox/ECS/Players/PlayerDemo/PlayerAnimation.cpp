#include "Engine/Utilities/TimeSteps.h"
#include "PlayerAnimation.h"

void PlayerAnimation::Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects)
{
	if (Object->Velocity.x != 0.0f)
	{
		float ElapsedTime = 0.0085f;
		if (Animation_TimeFrame >= ElapsedTime)
		{
			++Anime_Iterator;

			if (Anime_Iterator != WalkSprite_Animation.end())
				Object->DefaultTexture = *Anime_Iterator;

			Animation_TimeFrame = 0;
		}

		Animation_TimeFrame += std::abs(Object->Velocity.x) * TimeSteps::GetTimeSteps();

		if (Anime_Iterator == WalkSprite_Animation.end())
			Anime_Iterator =  WalkSprite_Animation.begin();
	}
}