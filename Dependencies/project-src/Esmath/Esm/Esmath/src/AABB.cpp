#include "AABB.h"
#include "Mat4x4.h"

namespace Esm {

    AABB::AABB()
    {
        for (int i = 0; i < 3; i++)
        {
            this->Min[i] = 0.0f;
            this->Max[i] = 0.0f;
        }
    }

    AABB::AABB(const Vec3& Min, const Vec3& Max)
    {
        this->CreateNewAABB(Min, Max);
    }

    AABB::AABB(const AABB& Box)
    {
        for (int i = 0; i < 3; i++)
        {
            this->Min[i] = Box.Min[i];
            this->Max[i] = Box.Max[i];
        }  
    }

    AABB& AABB::operator=(const AABB& Box)
    {
        for (int i = 0; i < 3; i++)
        {
            this->Min[i] = Box.Min[i];
            this->Max[i] = Box.Max[i];
        }
        return *this;
    }

    Vec3 AABB::ClosestPointAABBPt(const Vec3& Point)
    {
        Vec3 ClosestPointOnAABBToPoint = Point;

            if (Point.x < Min[0])
            {
                ClosestPointOnAABBToPoint.x = Min[0];
            }

            else if (Point.x > Max[0])
            {
                ClosestPointOnAABBToPoint.x = Max[0];
            }

            if (Point.y < Min[1])
            {
                ClosestPointOnAABBToPoint.y = Min[1];
            }

            else if (Point.y > Max[1])
            {
                ClosestPointOnAABBToPoint.y = Max[1];
            }

            if (Point.z < Min[2])
            {
                ClosestPointOnAABBToPoint.z = Min[2];
            }

            else if (Point.z > Max[2])
            {
                ClosestPointOnAABBToPoint.z = Max[2];
            }

            return ClosestPointOnAABBToPoint;
    }

    bool AABB::IntersectTest(const AABB& Box)
    {
        for (int i = 0; i < 3; i++)
        {
            if (!(this->Min[i] <= Box.Max[i] && this->Max[i] >= Box.Min[i]))
                return false;
        }

        return true;
    }

    void AABB::Update(const Vec3& Min, const Vec3& Max)
    {
        this->CreateNewAABB(Min, Max);
    }

    void AABB::CreateNewAABB(const Vec3& Min, const Vec3& Max)
    {
        this->Min[0] = Min.x;
        this->Min[1] = Min.y;
        this->Min[2] = Min.z;

        this->Max[0] = Max.x;
        this->Max[1] = Max.y;
        this->Max[2] = Max.z;
    }
}