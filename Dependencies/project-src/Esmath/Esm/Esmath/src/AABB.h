#pragma once
#include "Vec3.h"
#include "Quaternion.h"

namespace Esm{ 

	struct AABB
	{
		float Min[3];
		float Max[3];

		AABB();

		AABB(const Vec3& Min, const Vec3& Max);

		AABB(const AABB& Box);

		AABB& operator=(const AABB& Box);

		Vec3 ClosestPointAABBPt(const Vec3& Point);

		bool IntersectTest(const AABB& Object2);

		void Update(const Vec3& Min, const Vec3& Max);

	private:
		void CreateNewAABB(const Vec3& Min, const Vec3& Max);
	};
}