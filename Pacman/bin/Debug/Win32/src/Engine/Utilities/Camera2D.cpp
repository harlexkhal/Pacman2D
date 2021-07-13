#include "../Core/Window/NativeWindow/Window.h"
#include "Camera2D.h"

Camera2D::Camera2D(float radian, float Zoom)
	:Rotate(radian), Zoom(Zoom)
{}

void Camera2D::Update(Esm::Vec3 Position)
{
	this->Position = Position;

	Model.Translate(Position);
	Model.Rotate(Esm::Vec3(0, 0, 1), Esm::Radian(Rotate));
	Esm::Invert(Model);

	unsigned int Width = (unsigned int)Window::s_Window->GetWidth();
	unsigned int Height = (unsigned int)Window::s_Window->GetHeight();
	
	//To Prevent Division by Zero Error
	if (Height != 0 )
	Projection.SetOrthographic(Esm::Radian(Zoom), Width / Height, -1.0f, 1.0f);

    View = Projection * Model;
}