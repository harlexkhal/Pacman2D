#include "../Core/Window/NativeWindow/Window.h"

#include "InputManager.h"

bool InputManager::IsKeyPressed(int button)
{
	auto Window = (GLFWwindow*)Window::s_Window->GetNativeWindow();
	int State = glfwGetKey(Window, button);

	return State == GLFW_PRESS || State == GLFW_REPEAT;
}

bool InputManager::IsMouseButtonPressed(int button)
{
	auto Window = (GLFWwindow*)Window::s_Window->GetNativeWindow();
	auto state = glfwGetMouseButton(Window, button);

	return state == GLFW_PRESS;
}

std::tuple<float, float> InputManager::GetMousePosition()
{
	double x, y;
	auto Window = (GLFWwindow*)Window::s_Window->GetNativeWindow();
	glfwGetCursorPos(Window, &x, &y);

	return std::tuple<float, float>((float)x, (float)y);
}

float InputManager::GetMouseX()
{
	std::tuple<float, float> MousePosition = GetMousePosition();
	return (std::get<0>(MousePosition));
}

float InputManager::GetMouseY()
{
	std::tuple<float, float> MousePosition = GetMousePosition();
	return (std::get<1>(MousePosition));
}

Esm::Vec3 InputManager::GetMouseWorldPosition(Camera2D* Cam)
{
	float x = GetMouseX();
	float y = GetMouseY();

	unsigned int Width = (unsigned int)Window::s_Window->GetWidth();
	unsigned int Height = (unsigned int)Window::s_Window->GetHeight();

	float axisX = (2.0f * x) / Width - 1.0f;
	float axisY = 1.0f - (2.0f * y) / Height;
	axisX += Cam->Position.x;
	axisY += Cam->Position.y;

	return Esm::Vec3(axisX, axisY, 0.0f);
}