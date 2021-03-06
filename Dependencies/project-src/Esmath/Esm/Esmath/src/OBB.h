#pragma once
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4x4.h"

namespace Esm {

	struct OBB
	{
		float Center[3];
		float OrientationMatrix[3][3];
		float HalfExtent[3];

		OBB();

		OBB(const Vec3& Center, const Vec4& RotationAxis, const Vec3& HalfExtent);

		OBB(const OBB& OrientedBox);

		OBB& operator=(const OBB& OrientedBox);

		Esm::Vec3 ClosestPointOBBPt(const Esm::Vec3& Point) const;

		bool IntersectTest(const OBB& OrientedBox);

		void Update(const Vec3& Center, const Vec4& RotationAxis, const Vec3& HalfExtent);

	private:
		void CreateNewOBB(const Vec3& Center, const Vec4& RotationAxis, const Vec3& HalfExtent);
	};
}
