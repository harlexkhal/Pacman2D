#include <ctime>
#include <GLFW/glfw3.h>
#include "TimeSteps.h"
#include <iostream>
float TimeSteps::Ts = 0;
float TimeSteps::LastFrame = 0;
float TimeSteps::CurrentFrame = 0;

void TimeSteps::Update()
{
	/*CurrentFrame = static_cast<float>(clock()) / CLOCKS_PER_SEC;
	Ts = CurrentFrame - LastFrame;
	LastFrame = CurrentFrame;

	//---Making sure it doesn't render @ less than 60fps---
	if (Ts > (1.0f/60.0f))*/
		Ts = (1.0f / 100.0f);
}