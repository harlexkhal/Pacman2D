#pragma once

class RendererCommand
{
public:
	RendererCommand() {};
	virtual ~RendererCommand() {};

	virtual void ClearScreen(float r, float g, float b, float a) const = 0;
};