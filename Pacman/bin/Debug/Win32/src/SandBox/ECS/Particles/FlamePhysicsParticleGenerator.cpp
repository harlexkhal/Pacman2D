#include "FlamePhysicsParticleGenerator.h"

FlamePhysicsParticleGenerator::FlamePhysicsParticleGenerator(Renderer* ParticleSprite, Esm::Vec3 Color)
{
	this->ParticleGraphics = new GraphicsComponent(ParticleSprite);
	m_NumberOfParticles__ = 10000;
	m_SpawnRate = 10;
	this->Color = Color;

	for (int i = 0; i < m_NumberOfParticles__; i++)
	{
		Particles.emplace_back(new FlameParticle(Color));
	}
	LastParticle_It = Particles.begin();
}

FlamePhysicsParticleGenerator::~FlamePhysicsParticleGenerator()
{
	delete (this->ParticleGraphics);

	for (auto It : this->Particles)
		delete It;

	Particles.clear();
}

void FlamePhysicsParticleGenerator::Update(Camera2D* GameCamera, GameObject* Object, const std::vector<GameObject*>& WorldObjects)
{
	for (int i = 0; i < m_SpawnRate; i++)
	{
			for (auto It = LastParticle_It; It != Particles.end(); ++It)
			{
				if ((*It)->LifeSpan <= 0.0f)
				{
					SpawnParticle(*(*It));
					LastParticle_It = It;
					LastParticle_It++;

					if (LastParticle_It == Particles.end())
						LastParticle_It = Particles.begin();

					break;
				}
			}
	}
	
	for (auto& It : Particles)
	{
		if (It->LifeSpan > 0.0f)
		{ 
			//Update Particle Physics----------------------------------------
			It->LifeSpan -= TimeSteps::GetTimeSteps();
			It->Position += It->Velocity * TimeSteps::GetTimeSteps();
			It->Box.Update(It->Position - It->Size, It->Position + It->Size);

			It->aColorIntensity -= TimeSteps::GetTimeSteps();
			//Interpolating colors to form flame like particles
			It->Color.x -= 0.7 * TimeSteps::GetTimeSteps();
			It->Color.y -= 0.5 * TimeSteps::GetTimeSteps();
			It->Color.z -= TimeSteps::GetTimeSteps();
			//----------------------------------------------------------------
		}
	}

	for (auto& It : Particles)
	{
		if (It->LifeSpan > 0.0f)
		{
			ParticleGraphics->Update(GameCamera, It);
		}
	}
	m_Position = Object->Position;
	m_Size = Object->Size;
}

void FlamePhysicsParticleGenerator::SpawnParticle(Particle& Atom)
{
	//----------Movement of Flame Particle Controlled From here------------
	int Width = m_Size.x * 10;
	int Height = m_Size.y * 10;
	float RandomPositionParticleX__ = (-Width + ((rand() % (Width + Width + 1)))) / 100.0f;
	float RandomPositionParticleY__ = (-Height + ((rand() % (Height + Height + 1)))) / 100.0f;

	Atom.Position = m_Position + Esm::Vec3(RandomPositionParticleX__, RandomPositionParticleY__, 0.0f);
	Atom.LifeSpan = 1.0f;
	Atom.aColorIntensity = 1.0f;
	Atom.Color = Color;

	int RandomMovementX = (-Width + ((rand() % (Width + Width + 1))));
	int RandomMovementY = (-Height + ((rand() % (Height + Height + 1))));
	Atom.Velocity.x =  RandomMovementX / 100.0f;
	Atom.Velocity.y = RandomMovementY / 100.0f;
}