#pragma once
#include <Esmath/Esmath.h>
#include <glad/glad.h>
#include "../Renderer.h"
#include "OpenglShader.h"
#include "OpenglTexture.h"

class OpenglRenderer : public Renderer
{ 
public:
	OpenglRenderer(Shader* shader);
	virtual ~OpenglRenderer();

	virtual void OnRender(Camera2D* GameCamera, Texture* Tex, Esm::Mat4x4 Model, Esm::Vec4 rgba) override;
	virtual void OnRender(Camera2D* GameCamera, Texture* Tex, Esm::Vec3 Position, Esm::Vec3 Size, Esm::Vec4 rgba) override;

	virtual void CreateFrameBuffer() override;
	virtual void BindFrameBuffer() const override;
	virtual void UnBindFrameBuffer() const override;
	virtual void RenderFrameBuffer() override;
	virtual void RenderFrameBuffer(Camera2D* GameCamera, Esm::Mat4x4 Model, Esm::Vec3 Color) override;

private:
    Shader* shader;

	unsigned int VAO;
	unsigned int FBO;
	unsigned int TextureColorBuffer;

	void InitRenderData();
};