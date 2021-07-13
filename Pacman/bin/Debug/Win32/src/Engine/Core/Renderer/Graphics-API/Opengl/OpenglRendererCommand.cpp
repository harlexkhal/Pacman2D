#include <glad/glad.h>
#include "OpenglRendererCommand.h"

void OpenglRendererCommand::ClearScreen(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}