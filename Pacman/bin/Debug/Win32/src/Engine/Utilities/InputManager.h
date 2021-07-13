#pragma once
#include <GLFW/glfw3.h>
#include <tuple>
#include "Camera2D.h"
class InputManager
{
public:
    static bool IsKeyPressed(int keycode);

    static bool IsMouseButtonPressed(int button);
    static std::tuple<float, float>GetMousePosition();
    static float GetMouseX();
    static float GetMouseY();
    static Esm::Vec3 GetMouseWorldPosition(Camera2D* Cam);
};