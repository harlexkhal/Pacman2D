#include "PlayerInput.h"

void PlayerInput::Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects)
{
	if (InputManager::IsKeyPressed(GLFW_KEY_D))
		Object->Velocity.x = 0.7f;
	
	else if (InputManager::IsKeyPressed(GLFW_KEY_A))
		Object->Velocity.x = -0.7f;

	else
		Object->Velocity.x = 0.0f;
		
	const bool* OnGround = nullptr;
	for (auto& find : Object->Components)
	{
		OnGround = (bool*)find->Get((uint32_t)BroadCastMessage::ObjectOnGround);
		if (OnGround != nullptr)
			break;
	}

	if ((*OnGround) == true)
	{
		if (InputManager::IsKeyPressed(GLFW_KEY_W))
			Object->Velocity.y = 4.0f;
		else if (InputManager::IsKeyPressed(GLFW_KEY_S))
			Object->Velocity.y = -4.0f;
	}
}

void* PlayerInput::Get(uint32_t Message) const
{
	return nullptr;
}