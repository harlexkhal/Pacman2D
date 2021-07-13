#include <iostream>
#include <cmath>
#include "../Esmath/Esmath.h"


int main() {

	//rough sketch Test of mat4x4;
	
	Esm::Quaternion Q;
	//Q.SetToRotateAboutAxis(Esm::Vec3(0.0f,0.0f,1.0f),Esm::Radian(270.0f));
	//Q.Normalize();
	Q.FromObjectToWorldEuler(Esm::Vec3(0.0f, 0.0f, 180.0f));
	//Q.Normalize();
	std::cout << Esm::Degree(Q.GetRotationAngle()) << std::endl;
	Esm::Mat4x4 M;
	M.Rotate(Q);
	//M.Rotate(Esm::Vec3(0.0f, 0.0f, 1.0f), Esm::Radian(180.0f));
	Esm::Vec3 vvv(0.5f, 0.5f, 1.0f);
	vvv = M * vvv;
	std::cout << vvv.x << " " << vvv.y << std::endl;
	
	int i;
	int j;

	for (i=0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
			std::cout << M.Matrix[j][i]<<" ";

		std::cout << std::endl;
	}
	

	std::cin.get();
}