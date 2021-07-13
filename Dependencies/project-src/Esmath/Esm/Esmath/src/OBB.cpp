#include "OBB.h"

namespace Esm {

	OBB::OBB()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				OrientationMatrix[i][j] = 0.0f;

				if (i == 0)
				{
					HalfExtent[j] = 0.0f;
					Center[j] = 0.0f;
				}
			}
		}
	}

	OBB::OBB(const Vec3& Center, const Vec4& RotationAxis, const Vec3& HalfExtent)
	{
		this->CreateNewOBB(Center, RotationAxis, HalfExtent);
	}

	OBB::OBB(const OBB& OrientedBox)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				OrientationMatrix[i][j] = OrientedBox.OrientationMatrix[i][j];

				if (i == 0)
				{
					HalfExtent[j] = OrientedBox.HalfExtent[j];
					Center[j] = OrientedBox.Center[j];
				}
			}
		}
	}

	OBB& OBB::operator=(const OBB& OrientedBox)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				OrientationMatrix[i][j] = OrientedBox.OrientationMatrix[i][j];

				if (i == 0)
				{
					HalfExtent[j] = OrientedBox.HalfExtent[j];
					Center[j] = OrientedBox.Center[j];
				}
			}
		}

		return *this;
	}

	Vec3 OBB::ClosestPointOBBPt(const Esm::Vec3& Point) const
	{
		Vec3 d;
		d.x = Point.x - Center[0];
		d.y = Point.y - Center[1];
		d.z = Point.z - Center[2];

		Vec3 ClosestPointOnOBB;
		ClosestPointOnOBB.x = Center[0];
		ClosestPointOnOBB.y = Center[1];
		ClosestPointOnOBB.z = Center[2];

		for (int i = 0; i < 3; i++)
		{
			int j = 0;
			Esm::Vec3 Orient(OrientationMatrix[i][j++], OrientationMatrix[i][j++], OrientationMatrix[i][j]);

			//Projecting the point unto each RotationAxis
			float Dist = DotProduct(Orient, d);

			if (Dist > HalfExtent[i])
			{
				Dist = HalfExtent[i];
			}

			else if (Dist < -HalfExtent[i])
			{
				Dist = -HalfExtent[i];
			}

			ClosestPointOnOBB += Orient * Dist;
		}

		return ClosestPointOnOBB;
	}

	bool OBB::IntersectTest(const OBB& OrientedBox)
	{
		Vec3 C1(Center[0], Center[1], Center[2]);
		Vec3 C2(OrientedBox.Center[0], OrientedBox.Center[1], OrientedBox.Center[2]);

		Vec3 P2 = OrientedBox.ClosestPointOBBPt(C1);
		float Radius2 = DotProduct(C2 - P2, C2 - P2);

		Vec3 P1 = this->ClosestPointOBBPt(P2);

		float D = DotProduct(P1 - C2, P1 - C2);

		return (Radius2 >= D);
	}

	void OBB::Update(const Vec3& Center, const Vec4& RotationAxis, const Vec3& HalfExtent)
	{
		this->CreateNewOBB(Center, RotationAxis, HalfExtent);
	}

	void OBB::CreateNewOBB(const Vec3& Center, const Vec4& RotationAxis, const Vec3& HalfExtent)
	{
		//Making sure its a unit Vector...
		assert(RotationAxis.x <= 1.0f && RotationAxis.x >= 0.0f);
		assert(RotationAxis.y <= 1.0f && RotationAxis.y >= 0.0f);
		assert(RotationAxis.z <= 1.0f && RotationAxis.z >= 0.0f);

		//making x-axis Sin and y-axis Cos---Switching axis to Switch from Left Handed to Right. Tested-withOpengl--WorkSpace Right Handed
		float c = sin(RotationAxis.a);
		float s = cos(RotationAxis.a);

		float a = 1 - c;

		//column vec 1...
		OrientationMatrix[0][0] = ((RotationAxis.x * RotationAxis.x) * a) + c;
		OrientationMatrix[0][1] = ((RotationAxis.x * RotationAxis.y) * a) + RotationAxis.z * s;
		OrientationMatrix[0][2] = ((RotationAxis.x * RotationAxis.z) * a) - RotationAxis.y * s;

		//column vec2...
		OrientationMatrix[1][0] = ((RotationAxis.x * RotationAxis.y) * a) - RotationAxis.z * s;
		OrientationMatrix[1][1] = ((RotationAxis.y * RotationAxis.y) * a) + c;
		OrientationMatrix[1][2] = ((RotationAxis.y * RotationAxis.z) * a) + RotationAxis.x * s;

		//column vec3...
		OrientationMatrix[2][0] = ((RotationAxis.x * RotationAxis.z) * a) + RotationAxis.y * s;
		OrientationMatrix[2][1] = ((RotationAxis.y * RotationAxis.z) * a) - RotationAxis.x * s;
		OrientationMatrix[2][2] = ((RotationAxis.z * RotationAxis.z) * a) + c;

		this->Center[0] = Center.x;
		this->Center[1] = Center.y;
		this->Center[2] = Center.z;

		this->HalfExtent[0] = HalfExtent.x;
		this->HalfExtent[1] = HalfExtent.y;
		this->HalfExtent[2] = HalfExtent.z;
	}
}