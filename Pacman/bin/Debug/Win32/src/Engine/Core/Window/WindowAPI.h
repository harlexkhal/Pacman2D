#pragma once
#include "NativeWindow/Window.h"

class WindowAPI
{
public:
	static Window* WindowCreate(unsigned int Width, unsigned int Height, const char* Title);
};