#pragma once
#include <string>
#include "Graphics-API/Shader.h"
#include "Graphics-API/Texture.h"
#include "Graphics-API/Renderer.h"
#include "Graphics-API/RendererCommand.h"

class RendererAPI
{
public:
	static Shader* LoadShader(const char* src);
	static Texture* LoadTexture(const char* src);
	static Renderer* LoadRenderer(Shader* shader);

	static void ClearScreen(float r, float g, float b, float a);

private:
	 static RendererCommand* s_Instruction;
	 static RendererCommand* GetInstructionRendererAPI();
};