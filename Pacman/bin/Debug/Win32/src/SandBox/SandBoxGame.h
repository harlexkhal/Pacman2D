#pragma once
#include <string>
#include <map>
#include "Engine/Core/Window/WindowAPI.h"
#include "Engine/Core/Renderer/RendererAPI.h"
#include "Engine/GameObject.h"

class SandBoxGame
{
public:
	SandBoxGame();
	~SandBoxGame();
	void Init();
	
	void Update();
	void Render();

    Camera2D* GameCamera;
	Camera2D* MapCam;

	//--------------GameObjects--------------
	GameObject* Player;
	GameObject* Player2;
	GameObject* Grimm;
	GameObject* Dexter;
	GameObject* Ryler;

	GameObject* Terrain;
	GameObject* Terrain2;

	GameObject* Fire;
	GameObject* Fire2;

	GameObject* Cloud1;
	GameObject* Cloud2;
	GameObject* Cloud3;
	GameObject* Cloud4;
	GameObject* Cloud5;
	GameObject* Cannon;
	GameObject* Ball;
	//----------------------------------------

	std::vector<GameObject*> WorldObjects;

	Renderer* SpriteRenderer;
	Renderer* ParticleSprite;
	Renderer* Tracer;
	Renderer* MiniViewFrame;
	Renderer* GameMainFrame;

	//---Temporary Code For Testing
	std::vector<GameObject*> CamFollowStack;
	std::vector<GameObject*>::iterator CamFollow;
	//-----------------------------

	std::map<std::string, Shader*> Shaders;
	std::map<std::string, Texture*> Textures;
};