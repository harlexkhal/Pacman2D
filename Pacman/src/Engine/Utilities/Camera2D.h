#pragma once
#include <Esmath/Esmath.h>

class Camera2D
{
public:
	Camera2D(float radian, float Zoom);

	void Update(Esm::Vec3 Position = Esm::Vec3(0.0f,0.0f,0.0f));
	
	Esm::Mat4x4 Projection = { 1.0f };
	Esm::Mat4x4 View = { 1.0f };
	Esm::Mat4x4 Model = { 1.0f };
	Esm::Vec3 Position = { 0.0f,0.0f,0.0f };
	float Rotate;
	float Zoom;
};