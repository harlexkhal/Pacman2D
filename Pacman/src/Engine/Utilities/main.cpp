#include "SandBox/SandBoxGame.h"

int main() {
	
	Window* window = WindowAPI::WindowCreate(1200, 720, "SandBoxTest");
	SandBoxGame* Pac = new SandBoxGame;

	while (!window->WindowClose())
	{
		RendererAPI::ClearScreen(0.1f, 0.1f, 0.1f, 0.1f);

		Pac->Update();
		Pac->Render();

		window->PollEvents();
		window->SwapBuffers();
	}

	delete Pac;
	delete window;
}