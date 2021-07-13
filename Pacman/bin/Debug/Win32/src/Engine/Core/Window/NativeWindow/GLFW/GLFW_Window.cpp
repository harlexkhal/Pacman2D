#include <iostream>
#include "GLFW_Window.h"

GLFW_Window::GLFW_Window(float Width, float Height, const char* Title)
	:Window(Width, Height, Title)
{
	s_Window = this;
	Init();
}

GLFW_Window::~GLFW_Window()
{
	delete NativeWindow;
}

void GLFW_Window::PollEvents() const
{
	glfwPollEvents();
}

void GLFW_Window::SwapBuffers() const
{
	glfwSwapBuffers(NativeWindow);
}

void GLFW_Window::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	NativeWindow = glfwCreateWindow(Width, Height, Title, NULL, NULL);
	if (NativeWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(NativeWindow);

	glfwSetWindowSizeCallback(NativeWindow, [](GLFWwindow* Window, int width, int height)
	{
			s_Window->WindowResize(width, height);
			glViewport(0, 0, width, height);
	});

	glfwSetCursorPosCallback(NativeWindow, [](GLFWwindow* Window, double xpos, double ypos)
	{

	});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	glViewport(0, 0, Width, Height);
}

void GLFW_Window::WindowResize(unsigned int Width, unsigned int Height)
{
	this->Width = Width;
	this->Height = Height;
}
