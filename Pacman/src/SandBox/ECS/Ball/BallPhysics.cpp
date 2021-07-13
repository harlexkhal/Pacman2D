#include "Engine/Utilities/TimeSteps.h"
#include "../ObjectId.h"

#include "BallPhysics.h"
#include <iostream>
void BallPhysics::Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects)
{  
	/*v = v0 - gt => Displacement(p) = v*t using instantaneous velocity*/ 
	Object->Velocity.y -= Const_G_Acceleration * TimeSteps::GetTimeSteps();
	/*s = ut + 1/2 at^2*/
	Object->Position.y += (Object->Velocity.y * TimeSteps::GetTimeSteps()) + (0.5 * (-Const_G_Acceleration * (TimeSteps::GetTimeSteps() * TimeSteps::GetTimeSteps())));
	Object->Position.x += Object->Velocity.x * TimeSteps::GetTimeSteps();
	/*since Velocity = Displacement / Time
	Displacement = Velocity * Time
	so there for this also works for the new position of the object along y-axis
	Object->Position.y += Object->Velocity.y * TimeSteps::GetTimeSteps();*/

	//---Update AABB Depending on new Object Orientation before trying to check for any form of collision---
	Volume.Update(Object->Position - Object->Size, Object->Position + Object->Size);
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
				Const_G_Acceleration = 0.0f;

				if (Object->Velocity.y < 0.0f)
					Object->Velocity.y = 0.0f;
			}
		}
	}
	Cr = 0.5f;
}

void* BallPhysics::Get(uint32_t Message) const
{
	switch (Message)
	{
	case (uint32_t)BroadCastMessage::BoundingVolume: {
		const Esm::AABB* Box = &Volume;
		return ((void*)(Box));
	}
	}
}