#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Window.h"

class GLFW_Window : public Window
{
public:
	GLFW_Window(float Width, float Height, const char* Title);
	virtual ~GLFW_Window() override;

	inline virtual void* GetNativeWindow() const override { return NativeWindow; }
	inline virtual unsigned int GetHeight() const override { return Height; }
	inline virtual unsigned int GetWidth() const override { return Width; }

	inline virtual bool WindowClose() const override { return glfwWindowShouldClose(NativeWindow); }
	virtual void WindowResize(unsigned int Width, unsigned int Height) override;
	virtual void PollEvents()const override;
	virtual void SwapBuffers()const override;

private:
	void Init();
	GLFWwindow* NativeWindow;
};

