#include "GameObject.h"
#include "TargetIntegratorComponent.h"

TargetIntegratorComponent::TargetIntegratorComponent(Renderer* ObjectSprite, Texture* Tex, Esm::Vec3 Color)
{
	TrackObject = new TraceObject(Tex, Color);
	this->ObjectRenderer = new GraphicsComponent(ObjectSprite);
	ComponentTypeID = (uint32_t)DefaultComponentType::TargetIntegratorComponent;
}

TargetIntegratorComponent::~TargetIntegratorComponent()
{
	delete TrackObject;
	delete ObjectRenderer;
}

void TargetIntegratorComponent::Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects)
{
	const bool* Active = nullptr;
	for (auto& find : Object->Components)
	{
		Active = (bool*)find->Get((uint32_t)BroadCastMessage::ActiveTargetIntegrator);
		if (Active != nullptr)
			break;
	}

	if (*Active)
	{
		TrackObject->Velocity.y = Object->Velocity.x * sin(Object->Rotate.a);
		TrackObject->Velocity.x = Object->Velocity.y * cos(Object->Rotate.a);

		TrackObject->Position = Object->Position;

		//---Recalculates if any Object motion dynamics Changes---
		if (Stored_Rotation != Object->Rotate.a ||
			Stored_Velocity != Object->Velocity ||
			Stored_src_Position != Object->Position)
		{
			Positions.clear();
			for (int i = 0; i < 500; i++)
			{
				TrackObject->Velocity.y -= Const_G_Acceleration * TimeSteps::GetTimeSteps();;

				TrackObject->Position.y += (TrackObject->Velocity.y * TimeSteps::GetTimeSteps()) + (0.5 * (-Const_G_Acceleration * (TimeSteps::GetTimeSteps() * TimeSteps::GetTimeSteps()))) / 2.0f;
				TrackObject->Position.x += TrackObject->Velocity.x * TimeSteps::GetTimeSteps();

				Positions.emplace_back(TrackObject->Position);

				if (TrackObject->Position.y < -0.8f)
					break;
			}
		}

		//---To do Check if it has hit Target and stop Rendering---
		for (int i = 0; i < Positions.size(); i++)
		{
			TrackObject->Position = Positions[i];
			ObjectRenderer->Update(GameCamera, TrackObject);
		}

		Stored_Rotation = Object->Rotate.a;
		Stored_Velocity = Object->Velocity;
		Stored_src_Position = Object->Position;
	}
}