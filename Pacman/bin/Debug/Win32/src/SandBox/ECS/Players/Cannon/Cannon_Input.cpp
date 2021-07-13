#include "../../ObjectId.h"
#include "Cannon_Input.h"

void Cannon_Input::Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects)
{
	if (InputManager::IsKeyPressed(GLFW_KEY_UP))
	{
		Object->Rotate.x = 0;
		Object->Rotate.z = 1;
		Object->Rotate.y = 0;
		Object->Rotate.a += (Esm::Radian(30) * TimeSteps::GetTimeSteps());
	}

	else if (InputManager::IsKeyPressed(GLFW_KEY_DOWN))
	{
		Object->Rotate.x = 0;
		Object->Rotate.z = 1;
		Object->Rotate.y = 0;
		Object->Rotate.a -= (Esm::Radian(30) * TimeSteps::GetTimeSteps());
	}
	
	if (!ActivateTracer &&
		InputManager::IsKeyPressed(GLFW_KEY_SPACE))
	{
		 for (auto& It : WorldObjects)
		 {
			 if (It->ID == (uint32_t)ObjectTypeID::CannonBall)
			 {
				 It->Position = Object->Position;
				 It->Velocity.y = Object->Velocity.x * sin(Object->Rotate.a);
				 It->Velocity.x = Object->Velocity.y * cos(Object->Rotate.a);
			 }
		 }
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
		ActivateTracer = true;
	else
		ActivateTracer = false;
}

void* Cannon_Input::Get(uint32_t Message) const
{
	switch (Message)
	{
	case (uint32_t)BroadCastMessage::ActiveTargetIntegrator: {
		const bool* Track = &ActivateTracer;
		return ((void*)(Track));
	}
	}
}