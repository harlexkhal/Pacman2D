#include "Engine/Utilities/TimeSteps.h"
#include "../ObjectId.h"

#include "LandPhysics.h"

void LandPhysics::Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects)
{  
	Object->Velocity = Esm::Vec3(0.0f, 0.0f, 0.0f);
	Volume.Update(Object->Position - Object->Size, Object->Position + Object->Size);

	for (auto& It : WorldObjects)
	{
			const Esm::AABB* WorldObjectVolume = nullptr;
			for (auto& find : It->Components)
			{
				WorldObjectVolume = (Esm::AABB*)find->Get((uint32_t)BroadCastMessage::BoundingVolume);
				if (WorldObjectVolume != nullptr)
					break;
			}

			if (WorldObjectVolume != nullptr)
			{
				if (Volume.IntersectTest(*WorldObjectVolume))
				{
					this->Cr = 0.0f;
					if (It->ClassID == (uint32_t)ObjectTypeClassID::Ball)
					{
						this->Cr = 0.5f;
						It->Velocity.x *= 0.9f; //Adding Friction to the ball to come to a stop>>>
					}
					
					PhysicsComponent::LinearCollisionResponse(Object, It);
				}
			}
	}
}

void* LandPhysics::Get(uint32_t Message)const
{
	switch (Message)
	{
	case (uint32_t)BroadCastMessage::BoundingVolume: {
		const Esm::AABB* Box = &Volume;
		return ((void*)(Box));
	}
	}
}