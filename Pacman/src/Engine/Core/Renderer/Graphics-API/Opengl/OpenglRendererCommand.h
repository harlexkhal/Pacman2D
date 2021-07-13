#pragma once
#include "../RendererCommand.h"

class OpenglRendererCommand : public RendererCommand
{
public:
	OpenglRendererCommand() {};
	virtual ~OpenglRendererCommand() {};

	virtual void ClearScreen(float r, float g, float b, float a) const override;
};

