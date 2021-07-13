#include "Graphics-API/Opengl/OpenglShader.h"
#include "Graphics-API/Opengl/OpenglRenderer.h"
#include "Graphics-API/Opengl/OpenglTexture.h"
#include "Graphics-API/Opengl/OpenglRendererCommand.h"

#include "RendererAPI.h"

RendererCommand* RendererAPI::s_Instruction = RendererAPI::GetInstructionRendererAPI();

Shader* RendererAPI::LoadShader(const char* src)
{
	return (new OpenglShader(src));
}

Texture* RendererAPI::LoadTexture(const char* src)
{
	return (new OpenglTexture(src));
}

Renderer* RendererAPI::LoadRenderer(Shader* shader)
{
	return (new OpenglRenderer(shader));
}

void RendererAPI::ClearScreen(float r, float g, float b, float a)
{
	s_Instruction->ClearScreen(r, g, b, a);
}

RendererCommand* RendererAPI::GetInstructionRendererAPI()
{
	return new OpenglRendererCommand();
}