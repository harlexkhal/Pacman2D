#pragma once
#include <Esmath/Esmath.h>
#include "Engine/Utilities/Camera2D.h"

#include "Shader.h"
#include "Texture.h"

class Renderer
{ 
public:
	Renderer() {};
	virtual ~Renderer() {};

	virtual void OnRender(Camera2D* GameCamera, Texture* Tex, Esm::Mat4x4 Model, Esm::Vec4 rgba) = 0;
	virtual void OnRender(Camera2D* GameCamera, Texture* Tex, Esm::Vec3 Position, Esm::Vec3 Size, Esm::Vec4 rgba) = 0;

	virtual void CreateFrameBuffer() = 0;
	virtual void BindFrameBuffer() const = 0;
	virtual void UnBindFrameBuffer() const = 0;
	virtual void RenderFrameBuffer() = 0;
	virtual void RenderFrameBuffer(Camera2D* GameCamera, Esm::Mat4x4 Model, Esm::Vec3 Color) = 0;
};