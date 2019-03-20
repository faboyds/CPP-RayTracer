//
//  triangles.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "triangles.hpp"
#include "ray.hpp"

Triangles::Triangles(Transformation &transformation,
                     std::vector<Triangle> triangles): SceneObject(transformation), triangles(triangles)
{
}

//TODO missing implementation
inline bool Triangles::hit_object(ray &r, vec3 &result) {

    for (std::vector<Triangle>::iterator it = triangles.begin() ; it != triangles.end(); ++it) {
        //barycentric

        // get vertices coordinates
        vec3 A = vec3((*it).vertices[0].x, (*it).vertices[0].y, (*it).vertices[0].z);
        vec3 B = vec3((*it).vertices[1].x, (*it).vertices[1].y, (*it).vertices[1].z);
        vec3 C = vec3((*it).vertices[2].x, (*it).vertices[2].y, (*it).vertices[2].z);

        // compute plane's normal
        vec3 AB = B - A;
        vec3 AC = C - A;

        vec3 N = cross(AB, AC);
        N.make_unit_vector();
        double denom = dot(N, N);

        double area2 = N.length();

        // Step 1: finding P -------------------------------------------------------------------------------------------

        // check if ray and plane are parallel ?

        double NdotRayDirection = dot(N, r.direction());

        /**
        if (fabs(NdotRayDirection) < kEpsilon) // almost 0
            return false; // they are parallel so they don't intersect !
        **/

        // compute d parameter using equation 2
        double d = dot(N, A);

        // compute t (equation 3)
        double t = (dot(N, r.origin()) + d) / NdotRayDirection;

        // check if the triangle is in behind the ray
        if (t < 0) return false; // the triangle is behind

        // compute the intersection point using equation 1
        vec3 P = r.origin() + t * r.direction();


        // Step 2: inside-outside test ---------------------------------------------------------------------------------
        vec3 perp; // vector perpendicular to triangle's plane

        // edge 0
        vec3 edge0 = B - A;
        vec3 vp0 = P - A;
        perp = cross(edge0, vp0);
        if (dot(N, perp) < 0) return false; // P is on the right side

        // edge 1
        vec3 edge1 = C - B;
        vec3 vp1 = P - B;
        perp = cross(edge1, vp1);
        double u = perp.length() / area2;
        if (dot(N, perp) < 0)  return false; // P is on the right side

        // edge 2
        vec3 edge2 = A - C;
        vec3 vp2 = P - C;
        perp = cross(edge2, vp2);
        double v = C.length() / area2;
        if (dot(N, perp) < 0) return false; // P is on the right side;

        result = vec3((*it).material.red, (*it).material.green, (*it).material.blue);

        //u /= denom;
        //v /= denom;

        return true; // this ray hits the triangle
    }

    return false;
}

std::ostream& operator<<(std::ostream &strm, const Triangles &t) {
    return strm << "Triangles( transformation: " << t.transformation << " )";
}
