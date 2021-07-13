#include "Engine/Utilities/TimeSteps.h"
#include "Engine/GraphicsComponent.h"
#include "Engine/InputComponent.h"
#include "Engine/AnimationComponent.h"
#include "Engine/PhysicsComponent.h"
#include "Engine/TargetIntegratorComponent.h"
#include "Engine/GameObject.h"

//-----------------SandBoxGame ECS-----------------------------------------------------------------
#include "ECS/ObjectID.h"
#include "ECS/Particles/FlamePhysicsParticleGenerator.h"
#include "ECS/Players/NPCDemo/NPCBehaviour.h"
#include "ECS/Players/NPCDemo/NPCPhysics.h"
#include "ECS/Players/NPCDemo/NPCAnimation.h"
#include "ECS/Players/PlayerDemo/PlayerInput.h"
#include "ECS/Players/PlayerDemo/PlayerPhysics.h"
#include "ECS/Players/PlayerDemo/PlayerAnimation.h"
#include "ECS/Players/Cannon/Cannon_Input.h"
#include "ECS/Ball/BallPhysics.h"
#include "ECS/Terrain/LandPhysics.h"
//---------------------------------------------------------------------------------------------------

#include "SandBoxGame.h"

SandBoxGame::SandBoxGame()
{
	GameCamera = new Camera2D(0, 135.5f);
	MapCam = new Camera2D(0, 90.0f);
	Init();
}

SandBoxGame::~SandBoxGame()
{
	//---Lets Save the Operating System Some Stress of Deallocations :-)---
	delete GameCamera;
	delete MapCam;

	for (auto It : WorldObjects)
		delete It;

	CamFollowStack.clear();
	WorldObjects.clear();

	delete GameMainFrame;
	delete MiniViewFrame;
	delete SpriteRenderer;
	delete ParticleSprite;
	delete Tracer;
	
	for (std::pair<std::string, Shader*> It : Shaders)
		delete It.second;

	for (std::pair<std::string, Texture*> It : Textures)
		delete It.second;

	Shaders.clear();
	Textures.clear();
}

void SandBoxGame::Init()
{
	//Loading Shader Resources
	Shaders["Sprite"] = RendererAPI::LoadShader("src/SandBox/Assets/Shaders/SpriteShaders.glsl");
	Shaders["ParticleSprite"] = RendererAPI::LoadShader("src/SandBox/Assets/Shaders/ParticleShaders.glsl");
	Shaders["Tracer"] = RendererAPI::LoadShader("src/SandBox/Assets/Shaders/TracerShaders.glsl");
	Shaders["Screen"] = RendererAPI::LoadShader("src/SandBox/Assets/Shaders/Framebuffers_ScreenShaders.glsl");
	
	Textures["Particle"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/No-Animations/Particles/Fire/FireParticleType1.png");
	Textures["Terrain"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/No-Animations/Terrain-Sprite1.png");
	Textures["Cloud"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/No-Animations/Cloud.png");

	Textures["Grimm-Hunt"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ghosts/Grimm/Hunt/Grimm-Hunt.png");
	Textures["Dexter-Hunt"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ghosts/Dexter/Hunt/Dexter-Hunt.png");

	Textures["Ryler-Bird1"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/1.png");
	Textures["Ryler-Bird2"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/2.png");
	Textures["Ryler-Bird3"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/3.png");
	Textures["Ryler-Bird4"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/4.png");
	Textures["Ryler-Bird5"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/5.png");
	Textures["Ryler-Bird6"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/6.png");
	Textures["Ryler-Bird7"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/7.png");
	Textures["Ryler-Bird8"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/8.png");
	Textures["Ryler-Bird9"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/9.png");
	Textures["Ryler-Bird10"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/10.png");
	Textures["Ryler-Bird11"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/11.png");
	Textures["Ryler-Bird12"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/12.png");
	Textures["Ryler-Bird13"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/13.png");
	Textures["Ryler-Bird14"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ryler-TheBird/14.png");

	Textures["Cat1"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Cat/Walk/1.png");
	Textures["Cat2"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Cat/Walk/2.png");
	Textures["Cat3"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Cat/Walk/3.png");
	Textures["Cat4"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Cat/Walk/4.png");
	Textures["Cat5"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Cat/Walk/5.png");
	Textures["Cat6"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Cat/Walk/6.png");
	Textures["Cat7"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Cat/Walk/7.png");
	Textures["Cat8"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Cat/Walk/8.png");
	Textures["Cat9"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Cat/Walk/9.png");
	Textures["Cat10"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Cat/Walk/10.png");
	Textures["Cat11"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Cat/Walk/11.png");
	Textures["Cat12"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Cat/Walk/12.png");

	Textures["Ninja1"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ninja/1.png");
	Textures["Ninja2"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ninja/2.png");
	Textures["Ninja3"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ninja/3.png");
	Textures["Ninja4"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ninja/4.png");
	Textures["Ninja5"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ninja/5.png");
	Textures["Ninja6"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ninja/6.png");
	Textures["Ninja7"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ninja/7.png");
	Textures["Ninja8"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ninja/8.png");
	Textures["Ninja9"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ninja/9.png");
	Textures["Ninja10"] = RendererAPI::LoadTexture("src/SandBox/Assets/Textures/Animations/Ninja/10.png");

	//Renderer Initialization
	this->SpriteRenderer = RendererAPI::LoadRenderer(Shaders["Sprite"]);
	this->ParticleSprite = RendererAPI::LoadRenderer(Shaders["ParticleSprite"]);
	this->Tracer = RendererAPI::LoadRenderer(Shaders["Tracer"]);
	this->GameMainFrame = RendererAPI::LoadRenderer(Shaders["Screen"]);
	this->GameMainFrame->CreateFrameBuffer();
	this->MiniViewFrame = RendererAPI::LoadRenderer(Shaders["Sprite"]);
	this->MiniViewFrame->CreateFrameBuffer();

	AnimationComponent* SpriteAnimation;

	SpriteAnimation = new NPCAnimation();
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird1"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird2"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird3"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird4"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird5"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird6"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird7"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird8"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird9"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird10"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird11"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird12"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird13"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ryler-Bird14"]);
	Ryler = new GameObject(new GraphicsComponent(SpriteRenderer), new NPCBehaviour(), SpriteAnimation);
	Ryler->PushComponent(new NPCPhysics());
	Ryler->ClassID = (uint32_t)ObjectTypeClassID::AI;
	Ryler->ID = (uint32_t)ObjectTypeID::NPC1;
	Ryler->DefaultTexture = Textures["Ryler-Bird1"];
	Ryler->Position = Esm::Vec3(0.0f, 0.8f, 0.0f);
	Ryler->Size = Esm::Vec3(0.08f, 0.08f, 0.0f);
	Ryler->Velocity = Esm::Vec3(0.6f, 0.1f, 0.0f);
	Ryler->mass = 70.0f;//kg

	SpriteAnimation = new NPCAnimation();
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Cat1"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Cat2"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Cat3"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Cat4"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Cat5"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Cat6"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Cat7"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Cat8"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Cat9"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Cat10"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Cat11"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Cat12"]);
	Player = new GameObject(new GraphicsComponent(SpriteRenderer), new PlayerInput(), SpriteAnimation);
	Player->PushComponent(new PlayerPhysics());
	Player->ClassID = (uint32_t)ObjectTypeClassID::Player;
	Player->ID = (uint32_t)ObjectTypeID::Player1;
	Player->DefaultTexture = Textures["Cat1"];
	Player->Position = Esm::Vec3(-1.1f, -0.5f, 0.0f);
	Player->Size = Esm::Vec3(0.1f, 0.1f, 0.0f);
	Player->Velocity = Esm::Vec3(0.0f, 0.0f, 0.0f);
	Player->mass = 70.0f;//kg

	SpriteAnimation = new NPCAnimation();
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ninja1"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ninja2"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ninja3"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ninja4"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ninja5"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ninja6"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ninja7"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ninja8"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ninja9"]);
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Ninja10"]);
	Player2 = new GameObject(new GraphicsComponent(SpriteRenderer), new NPCBehaviour(), SpriteAnimation);
	Player2->PushComponent(new NPCPhysics());
	Player2->ClassID = (uint32_t)ObjectTypeClassID::AI;
	Player2->ID = (uint32_t)ObjectTypeID::NPC2;
	Player2->DefaultTexture = Textures["Ninja1"];
	Player2->Position = Esm::Vec3(-0.6f, -0.5f, 0.0f);
	Player2->Size = Esm::Vec3(0.1f, 0.1f, 0.0f);
	Player2->Velocity = Esm::Vec3(0.9f, 0.0f, 0.0f);
	Player2->mass = 70.0f;//kg

	SpriteAnimation = new NPCAnimation();
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Grimm-Hunt"]);
	Grimm = new GameObject(new GraphicsComponent(SpriteRenderer), new NPCBehaviour(), SpriteAnimation);
	Grimm->PushComponent(new NPCPhysics());
	Grimm->PushComponent(new FlamePhysicsParticleGenerator(ParticleSprite));
	Grimm->ClassID = (uint32_t)ObjectTypeClassID::AI;
	Grimm->ID = (uint32_t)ObjectTypeID::NPC3;
	Grimm->DefaultTexture = Textures["Grimm-Hunt"];
	Grimm->Position = Esm::Vec3(0.5f, -0.4f, 0.0f);
	Grimm->Size = Esm::Vec3(0.1f, 0.1f, 0.0f);
	Grimm->Velocity = Esm::Vec3(0.9f, 0.0f, 0.0f);
	Grimm->mass = 70.0f;//kg

	SpriteAnimation = new NPCAnimation();
	SpriteAnimation->PushBack_WalkSprite_Animation(Textures["Dexter-Hunt"]);
	Dexter = new GameObject(new GraphicsComponent(SpriteRenderer), new NPCBehaviour(), SpriteAnimation);
	Dexter->PushComponent(new NPCPhysics());
	Dexter->ClassID = (uint32_t)ObjectTypeClassID::AI;
	Dexter->ID = (uint32_t)ObjectTypeID::NPC4;
	Dexter->DefaultTexture = Textures["Dexter-Hunt"];
	Dexter->Position = Esm::Vec3(0.6f, -0.3f, 0.0f);
	Dexter->Size = Esm::Vec3(0.1f, 0.1f, 0.0f);
	Dexter->Velocity = Esm::Vec3(0.9f, 0.0f, 0.0f);
	Dexter->mass = 70.0f;//kg

	Terrain = new GameObject(new GraphicsComponent(SpriteRenderer), new LandPhysics());
	Terrain->ClassID = (uint32_t)ObjectTypeClassID::Terrain;
	Terrain->ID = (uint32_t)ObjectTypeID::LandTerrain;
	Terrain->DefaultTexture = Textures["Terrain"];
	Terrain->Position = Esm::Vec3(-0.8f, -0.8f, 0.0f);
	Terrain->Size = Esm::Vec3(0.5f, 0.2f, 0.0f);
	Terrain->Velocity = Esm::Vec3(0.0f, 0.0f, 0.0f);
	Terrain->mass = 100000.0f;//kg

	Terrain2 = new GameObject(new GraphicsComponent(SpriteRenderer), new LandPhysics());
	Terrain2->ClassID = (uint32_t)ObjectTypeClassID::Terrain;
	Terrain2->ID = (uint32_t)ObjectTypeID::LandTerrain;
	Terrain2->DefaultTexture = Textures["Terrain"];
	Terrain2->Position = Esm::Vec3(0.8f, -0.8f, 0.0f);
	Terrain2->Size = Esm::Vec3(0.5f, 0.2f, 0.0f);
	Terrain2->Velocity = Esm::Vec3(0.0f, 0.0f, 0.0f);
	Terrain2->mass = 100000.0f;//kg
	
	Cloud1 = new GameObject(new GraphicsComponent(SpriteRenderer));
	Cloud1->ClassID = (uint32_t)ObjectTypeClassID::Cloud;
	Cloud1->ID = (uint32_t)ObjectTypeID::SkyCloud;
	Cloud1->DefaultTexture = Textures["Cloud"];
	Cloud1->Position = Esm::Vec3(0.8f, 0.3f, 0.0f);
	Cloud1->Size = Esm::Vec3(0.1f, 0.05f, 0.0f);

	Cloud2 = new GameObject(new GraphicsComponent(SpriteRenderer));
	Cloud2->ClassID = (uint32_t)ObjectTypeClassID::Cloud;
	Cloud2->ID = (uint32_t)ObjectTypeID::SkyCloud;
	Cloud2->DefaultTexture = Textures["Cloud"];
	Cloud2->Position = Esm::Vec3(0.5f, 0.25f, 0.0f);
	Cloud2->Size = Esm::Vec3(0.1f, 0.05f, 0.0f);

	Cloud3 = new GameObject(new GraphicsComponent(SpriteRenderer));
	Cloud3->ClassID = (uint32_t)ObjectTypeClassID::Cloud;
	Cloud3->ID = (uint32_t)ObjectTypeID::SkyCloud;
	Cloud3->DefaultTexture = Textures["Cloud"];
	Cloud3->Position = Esm::Vec3(-0.4f, 0.2f, 0.0f);
	Cloud3->Size = Esm::Vec3(0.1f, 0.05f, 0.0f);

	Cloud4 = new GameObject(new GraphicsComponent(SpriteRenderer));
	Cloud4->ClassID = (uint32_t)ObjectTypeClassID::Cloud;
	Cloud4->ID = (uint32_t)ObjectTypeID::SkyCloud;
	Cloud4->DefaultTexture = Textures["Cloud"];
	Cloud4->Position = Esm::Vec3(-0.7f, 0.31f, 0.0f);
	Cloud4->Size = Esm::Vec3(0.1f, 0.05f, 0.0f);
	
	Cloud5 = new GameObject(new GraphicsComponent(SpriteRenderer));
	Cloud5->ClassID = (uint32_t)ObjectTypeClassID::Cloud;
	Cloud5->ID = (uint32_t)ObjectTypeID::SkyCloud;
	Cloud5->DefaultTexture = Textures["Cloud"];
	Cloud5->Position = Esm::Vec3(0.0f, 0.36f, 0.0f);
	Cloud5->Size = Esm::Vec3(0.1f, 0.05f, 0.0f);

	Fire = new GameObject();
	Fire->PushComponent(new FlamePhysicsParticleGenerator(ParticleSprite));
	Fire->ClassID = (uint32_t)ObjectTypeClassID::Particle;
	Fire->ID = (uint32_t)ObjectTypeID::Fire;
	Fire->Position = Esm::Vec3(-0.9f, -0.6f, 0.0f);
	Fire->Size = Esm::Vec3(0.5f, 1.7f, 0.0f);

	Fire2 = new GameObject();
	Fire2->PushComponent(new FlamePhysicsParticleGenerator(ParticleSprite));
	Fire2->ClassID = (uint32_t)ObjectTypeClassID::Particle;
	Fire2->ID = (uint32_t)ObjectTypeID::Fire;
	Fire2->Position = Esm::Vec3(0.9f, -0.6f, 0.0f);
	Fire2->Size = Esm::Vec3(0.6f, 1.9f, 0.0f);
	
	Cannon = new GameObject(new GraphicsComponent(SpriteRenderer), new Cannon_Input(), new TargetIntegratorComponent(Tracer, Textures["Cloud"]));
	Cannon->ClassID = (uint32_t)ObjectTypeClassID::Cannon;
	Cannon->ID = (uint32_t)ObjectTypeID::Cannon1;
	Cannon->DefaultTexture = Textures["Cloud"];
	Cannon->Position = Esm::Vec3(-1.0f, -0.5f, 0.0f);
	Cannon->Size = Esm::Vec3(0.1f, 0.05f, 0.0f);
	Cannon->Velocity = Esm::Vec3(4.0f, 4.0f, 0.0f);
	Cannon->Rotate = Esm::Vec4(0, 0, 1, Esm::Radian(45.0f));

	Ball = new GameObject(new GraphicsComponent(SpriteRenderer), new BallPhysics(), new FlamePhysicsParticleGenerator(ParticleSprite));
	Ball->ClassID = (uint32_t)ObjectTypeClassID::Ball;
	Ball->ID = (uint32_t)ObjectTypeID::CannonBall;
	Ball->DefaultTexture = Textures["Cloud"];
	Ball->Position = Esm::Vec3(-1.0f, -0.5f, 0.0f);
	Ball->Size = Esm::Vec3(0.05f, 0.05f, 0.0f);
	Ball->mass = 10.0f;//kg

	WorldObjects.emplace_back(Player);
	WorldObjects.emplace_back(Terrain);
	WorldObjects.emplace_back(Terrain2);
	WorldObjects.emplace_back(Cloud1);
	WorldObjects.emplace_back(Cloud2);
	WorldObjects.emplace_back(Cloud3);
	WorldObjects.emplace_back(Cloud4);
	WorldObjects.emplace_back(Cloud5);
	WorldObjects.emplace_back(Dexter);
	WorldObjects.emplace_back(Ryler);
	WorldObjects.emplace_back(Player2);
	WorldObjects.emplace_back(Fire);
	WorldObjects.emplace_back(Fire2);
	WorldObjects.emplace_back(Grimm);
	WorldObjects.emplace_back(Cannon);
	WorldObjects.emplace_back(Ball);

	//Temporary Codes For Testing---TerrainGeneration========================================================
	unsigned int index = WorldObjects.size();
	float offset = 0.8f + 1.6f;
	for (int i = index; i < (index + 10); i++)
	{
		WorldObjects.emplace_back(new GameObject(new GraphicsComponent(SpriteRenderer), new LandPhysics()));
		WorldObjects[i]->ClassID = (uint32_t)ObjectTypeClassID::Terrain;
		WorldObjects[i]->ID = (uint32_t)ObjectTypeID::LandTerrain;
		WorldObjects[i]->DefaultTexture = Textures["Terrain"];
		WorldObjects[i]->Position = Esm::Vec3(offset, -0.8f, 0.0f);
		WorldObjects[i]->Size = Esm::Vec3(0.5f, 0.2f, 0.0f);
		WorldObjects[i]->Velocity = Esm::Vec3(0.0f, 0.0f, 0.0f);
		WorldObjects[i]->mass = 100000.0f;//kg	
		offset += 1.6f;
	}

	index = WorldObjects.size();
	offset = 0.0f + 0.3f;
	int p = 0;
	float Yoffset[5] = { 0.36f, 0.2f, 0.1f, 0.0f, 0.15f };
	for (int i = index; i < (index + 50); i++)
	{
		WorldObjects.emplace_back(new GameObject(new GraphicsComponent(SpriteRenderer)));
		WorldObjects[i]->ClassID = (uint32_t)ObjectTypeClassID::Cloud;
		WorldObjects[i]->ID = (uint32_t)ObjectTypeID::SkyCloud;
		WorldObjects[i]->DefaultTexture = Textures["Cloud"];
		WorldObjects[i]->Position = Esm::Vec3(offset, Yoffset[p], 0.0f);
		WorldObjects[i]->Size = Esm::Vec3(0.1f, 0.05f, 0.0f);

		p++;
		if (p == 5)
			p = 0;

		offset += 0.3f;
	}
	//==================================================================================================

	//-----Temporary Codes for Testing------
	CamFollowStack.emplace_back(Player);
	CamFollowStack.emplace_back(Player2);
	CamFollowStack.emplace_back(Dexter);
	CamFollowStack.emplace_back(Ryler);
	CamFollowStack.emplace_back(Grimm);
	CamFollowStack.emplace_back(Ball);

	CamFollow = CamFollowStack.begin();
	//--------------------------------------
}

void SandBoxGame::Update()
{
	TimeSteps::Update();

	GameMainFrame->BindFrameBuffer();
	RendererAPI::ClearScreen(0.2f, 0.2f, 0.2f, 0.2f);
		for (auto& It : WorldObjects)
			It->Update(GameCamera, WorldObjects);

		MiniViewFrame->BindFrameBuffer();
		RendererAPI::ClearScreen(0.0f, 0.5f, 0.7f, 1.0f);
		for (auto& It : WorldObjects)
			It->Update(MapCam, WorldObjects);

		GameMainFrame->UnBindFrameBuffer();
		MiniViewFrame->UnBindFrameBuffer();

		//--------------Temporary Codes For Testing---------------------
		if (InputManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			CamFollow++;
			if (CamFollow == CamFollowStack.end())
				CamFollow = CamFollowStack.begin();
		}
		//--------------------------------------------------------------

		GameCamera->Update((*CamFollow)->Position);
		MapCam->Update(Ball->Position);
}

void SandBoxGame::Render()
{
	GameMainFrame->BindFrameBuffer();
	for (auto& It : WorldObjects)
		It->Render(GameCamera);
	
	MiniViewFrame->BindFrameBuffer();
	for (auto& It : WorldObjects)
		It->Render(MapCam);

	this->GameMainFrame->RenderFrameBuffer();
	Esm::Mat4x4 ObjectModel(1.0f);
	ObjectModel.Translate(GameCamera->Position - Esm::Vec3(1.8f, 1.8f, 0.0f));
	ObjectModel.Scale(Esm::Vec3(0.8f, 0.8f, 0.0f));
	this->MiniViewFrame->RenderFrameBuffer(GameCamera, ObjectModel, Esm::Vec3(0.0f, 0.0f, 0.0f));
	
	GameMainFrame->UnBindFrameBuffer();
	MiniViewFrame->UnBindFrameBuffer();
}