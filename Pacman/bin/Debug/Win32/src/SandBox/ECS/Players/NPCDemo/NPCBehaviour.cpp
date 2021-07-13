#include "../../ObjectID.h"
#include "NPCBehaviour.h"

void NPCBehaviour::Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects)
{
	Object->Velocity.x = 0.9f;
	
	for (auto& It : WorldObjects)
	{
		//---------------------------------------AI_Temp_Jump-----------------------------------------------------------
		if (It->ClassID == (uint32_t)ObjectTypeClassID::Terrain)
		{
				if (Object->Velocity.x > 0)
				{
					if (Object->Position.x + Object->Size.x >= It->Position.x + It->Size.x &&
						Object->Position.x - Object->Size.x < It->Position.x + It->Size.x)
					{
						Object->Velocity.y = 4.0f;
					}
				}

				else
				{
					if (Object->Position.x - Object->Size.x <= It->Position.x - It->Size.x &&
						Object->Position.x + Object->Size.x > It->Position.x - It->Size.x)
					{
						Object->Velocity.y = 4.0f;
					}
				}
		}

		const std::vector<GameObject*>* CollisionQueue = nullptr;
		for (auto& find : It->Components)
		{
			CollisionQueue = (std::vector<GameObject*>*)find->Get((uint32_t)BroadCastMessage::CollidedObjectsList);
			if (CollisionQueue != nullptr)
				break;
		}
	}
}