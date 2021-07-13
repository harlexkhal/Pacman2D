#include "NativeWindow/GLFW/GLFW_Window.h"
#include "WindowAPI.h"

Window* Window::s_Window;
Window* WindowAPI::WindowCreate(unsigned int Width, unsigned int Height, const char* Title)
{
    return (new GLFW_Window(Width, Height, Title));
}
