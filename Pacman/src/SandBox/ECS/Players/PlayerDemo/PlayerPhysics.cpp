#include "Engine/Utilities/TimeSteps.h"
#include "../../ObjectId.h"

#include "PlayerPhysics.h"

void PlayerPhysics::Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects)
{  
	/*v = v0 - gt => Displacement(p) = v*t using instantaneous velocity*/ 
	Object->Velocity.y -= Const_G_Acceleration * TimeSteps::GetTimeSteps();
	/*s = ut + 1/2 at^2*/
	Object->Position.y += (Object->Velocity.y * TimeSteps::GetTimeSteps()) + (0.5 * (-Const_G_Acceleration * (TimeSteps::GetTimeSteps() * TimeSteps::GetTimeSteps())));
	/*since Velocity = Displacement / Time
	Displacement = Velocity * Time
	so there for this also works for the new position of the object along y-axis
	Object->Position.y += Object->Velocity.y * TimeSteps::GetTimeSteps();*/

	if (Object->Position.y < -0.9f)
		Object->Position = Esm::Vec3(-0.8f, -0.2f, 0.0f);

	if (Object->Velocity.x != 0.0f)
	{
		Object->Position.x += Object->Velocity.x * TimeSteps::GetTimeSteps();
		if (Object->Velocity.x > 0)
		{
			Object->Rotate.x = 0;
			Object->Rotate.z = 0;
			Object->Rotate.y = 1;
			Object->Rotate.a = Esm::Radian(180);
		}
		else
		{
			Object->Rotate.x = 0;
			Object->Rotate.z = 0;
			Object->Rotate.y = 1;
			Object->Rotate.a = Esm::Radian(0);
		}
	}

	//---Update AABB Depending on new Object Orientation before trying to check for any form of collision---
	Volume.Update(Object->Position - Object->Size, Object->Position + Object->Size);

	this->OnGround = false;
	Const_G_Acceleration = 9.8f;
	for (auto& It : WorldObjects)
	{
		if (It->ClassID == (uint32_t)ObjectTypeClassID::Terrain)
		{
			const Esm::AABB* WorldObjectVolume = nullptr;
			for (auto& find : It->Components)
			{
				WorldObjectVolume = (Esm::AABB*)find->Get((uint32_t)BroadCastMessage::BoundingVolume);
				if (WorldObjectVolume != nullptr)
					break;
			}

			if (Volume.IntersectTest(*WorldObjectVolume))
			{
				OnGround = true;
				Const_G_Acceleration = 0.0f;

				if (Object->Velocity.y < 0.0f)
					Object->Velocity.y = 0.0f;
			}
		}
	}
}

void* PlayerPhysics::Get(uint32_t Message) const
{
	switch (Message)
	{
	case (uint32_t)BroadCastMessage::BoundingVolume: {
		const Esm::AABB* Box = &Volume;
		return ((void*)(Box));
	}

	case (uint32_t)BroadCastMessage::ObjectOnGround: {
		const bool* LandLevel = &OnGround;
		return ((void*)(LandLevel));
	}
	}
}