#pragma once

class Window
{
public:
	Window(float Width, float Height, const char* Title)
		: Width(Width), Height(Height), Title(Title) {};
	virtual ~Window() {};

	 virtual void* GetNativeWindow() const = 0;
	 virtual unsigned int GetHeight() const = 0;
	 virtual unsigned int GetWidth() const = 0;

	 virtual bool WindowClose() const = 0;
	 virtual void WindowResize(unsigned int Width, unsigned int Height) = 0;
	 virtual void PollEvents() const = 0;
	 virtual void SwapBuffers() const = 0;
	
	 static Window* s_Window;
protected:
	unsigned int Height;
	unsigned int Width;
	const char* Title;
};