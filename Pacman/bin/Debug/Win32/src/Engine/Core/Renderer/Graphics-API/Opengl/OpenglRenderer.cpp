#include <Esmath/Esmath.h>
#include "../../../Window/NativeWindow/Window.h"
#include "OpenglShader.h"
#include "OpenglRenderer.h"

OpenglRenderer::OpenglRenderer(Shader* shader)
{
	this->shader = shader;
	this->VAO = -1;
	/*Only GameFramebuffers Renderers are allowed to activate their FBOs and TextureColorBuffer*/
	this->FBO = -1;
	this->TextureColorBuffer = -1;
	InitRenderData();
}

OpenglRenderer::~OpenglRenderer()
{
	glDeleteVertexArrays(1, &this->VAO);

	if (this->FBO != -1)
	{
		glDeleteTextures(1, &this->TextureColorBuffer);
		glDeleteFramebuffers(1, &this->FBO);
	}
}

void OpenglRenderer::OnRender(Camera2D* GameCamera, Texture* Tex, Esm::Mat4x4 Model, Esm::Vec4 rgba)
{
	shader->Use();
	shader->SetFloat4("ParticleColor", rgba.x, rgba.y, rgba.z, rgba.a);
	shader->SetMat4FLoatV("Model", &Model.Matrix[0][0]);
	shader->SetMat4FLoatV("CamView", &GameCamera->View.Matrix[0][0]);
	
	if (Tex)
		Tex->Bind();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenglRenderer::OnRender(Camera2D* GameCamera, Texture* Tex, Esm::Vec3 Position, Esm::Vec3 Size, Esm::Vec4 rgba)
{
	shader->Use();
	shader->SetFloat4("ParticleColor", rgba.x, rgba.y, rgba.z, rgba.a);
	shader->SetFloat2("OffsetPosition", Position.x, Position.y);
	shader->SetFloat2("Scale", Size.x, Size.y);
	shader->SetMat4FLoatV("CamView", &GameCamera->View.Matrix[0][0]);

	if (Tex)
		Tex->Bind();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenglRenderer::CreateFrameBuffer()
{
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &TextureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, TextureColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::s_Window->GetWidth(), Window::s_Window->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TextureColorBuffer, 0);

	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int RBO;
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::s_Window->GetWidth(), Window::s_Window->GetHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void OpenglRenderer::BindFrameBuffer() const
{
	if (this->FBO == -1)
	{
		std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer has not been created!" << std::endl;
		assert(false);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void OpenglRenderer::UnBindFrameBuffer() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenglRenderer::RenderFrameBuffer()
{
	if (this->FBO == -1)
	{
		std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer has not been created!" << std::endl;
		assert(false);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	shader->Use();
	glBindTexture(GL_TEXTURE_2D, TextureColorBuffer);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glViewport(0, 0, Window::s_Window->GetWidth(), Window::s_Window->GetHeight());
}

void OpenglRenderer::RenderFrameBuffer(Camera2D* GameCamera, Esm::Mat4x4 Model, Esm::Vec3 Color)
{
	if (this->FBO == -1)
	{
		std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer has not been created!" << std::endl;
		assert(false);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	shader->Use();
	shader->SetFloat3("Color", Color.x, Color.y, Color.z);
	shader->SetMat4FLoatV("Model", &Model.Matrix[0][0]);
	shader->SetMat4FLoatV("CamView", &GameCamera->View.Matrix[0][0]);

	glBindTexture(GL_TEXTURE_2D, TextureColorBuffer);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glViewport(0, 0, Window::s_Window->GetWidth(), Window::s_Window->GetHeight());
}

void OpenglRenderer::InitRenderData()
{
	float Vertices[] = 
	{  
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f
	};
	unsigned int Index[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	unsigned int VBO;
	unsigned int EBO;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, Index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}