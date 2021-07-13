#include "GameObject.h"
#include "PhysicsComponent.h"
#include <cmath>
void PhysicsComponent::LinearCollisionResponse(GameObject* OwnedObject, GameObject* WorldObject)
{
	Esm::Vec3 RelativeVelocity = OwnedObject->Velocity - WorldObject->Velocity;
	Esm::Vec3 ContactNormal = OwnedObject->Position - WorldObject->Position;

	float Vr = Esm::DotProduct(RelativeVelocity, ContactNormal);
	
	if (Vr < 0.0f)
	{
		float j;
		j = (-(1.0f + Cr) * (Vr)) / ((Esm::DotProduct(ContactNormal , ContactNormal)) *
				                    ((1 / OwnedObject->mass) + (1 / WorldObject->mass)));

		OwnedObject->Velocity += ((j * ContactNormal) / OwnedObject->mass);
		WorldObject->Velocity -= ((j * ContactNormal) / WorldObject->mass);
	}
}