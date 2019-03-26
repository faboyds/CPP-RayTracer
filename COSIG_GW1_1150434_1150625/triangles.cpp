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

inline double Triangles::hit_object(ray &r, vec3 &normal) {

    double lowestT = 99999;

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

        double area = N.length()/2;

        N.make_unit_vector();


        // matrix are 10x10 to be used in the utils. the real dimension is only 3x3

        double matrixA[3][3];
        matrixA[0][0] = A.x() - r.origin().x();
        matrixA[0][1] = A.x() - C.x();
        matrixA[0][2] = r.direction().x();
        matrixA[1][0] = A.y() - r.origin().y();
        matrixA[1][1] = A.y() - C.y();
        matrixA[1][2] = r.direction().y();
        matrixA[2][0] = A.z() - r.origin().z();
        matrixA[2][1] = A.z() - C.z();
        matrixA[2][2] = r.direction().z();


        double matrixB[3][3];
        matrixB[0][0] = A.x() - B.x();
        matrixB[0][1] = A.x() - r.origin().x();
        matrixB[0][2] = r.direction().x();
        matrixB[1][0] = A.y() - B.y();
        matrixB[1][1] = A.y() - r.origin().y();
        matrixB[1][2] = r.direction().y();
        matrixB[2][0] = A.z() - B.z();
        matrixB[2][1] = A.z() - r.origin().z();
        matrixB[2][2] = r.direction().z();

        double matrixT[3][3];
        matrixT[0][0] = A.x() - B.x();
        matrixT[0][1] = A.x() - C.x();
        matrixT[0][2] = A.x() - r.origin().x();
        matrixT[1][0] = A.y() - B.y();
        matrixT[1][1] = A.y() - C.y();
        matrixT[1][2] = A.y() - r.origin().y();
        matrixT[2][0] = A.z() - B.z();
        matrixT[2][1] = A.z() - C.z();
        matrixT[2][2] = A.z() - r.origin().z();


        double mm[3][3];
        mm[0][0] = A.x() - B.x();
        mm[0][1] = A.x() - C.x();
        mm[0][2] = r.direction().x();
        mm[1][0] = A.y() - B.y();
        mm[1][1] = A.y() - C.y();
        mm[1][2] = r.direction().y();
        mm[2][0] = A.z() - B.z();
        mm[2][1] = A.z() - C.z();
        mm[2][2] = r.direction().z();

        double Am = tmutl::determinant2(mm);

        double beta = tmutl::determinant2(matrixA) / Am;
        double gama = tmutl::determinant2(matrixB) / Am;
        double t = tmutl::determinant2(matrixT) / Am;

        double alpha = 1 - beta - gama;

        if(beta > 1 || beta < 0) continue;
        if(gama > 1 || gama < 0) continue;
        if(alpha > 1 || alpha < 0) continue;

        vec3 point = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
        normal = (*it).normalVector;

        if(t > 0 && t < lowestT) {
            lowestT = t;
        }

        /*
        //compute plane's normal
        vec3 AB = B - A;
        vec3 AC = C - A;

        vec3 N = cross(AB, AC);
        N.make_unit_vector();
        double denom = dot(N, N);

        double area2 = N.length();

        // Step 1: finding P -------------------------------------------------------------------------------------------

        // check if ray and plane are parallel ?

        double NdotRayDirection = dot(N, r.direction());

        *//*
*/
/**
        if (fabs(NdotRayDirection) < kEpsilon) // almost 0
            return false; // they are parallel so they don't intersect !
        **//*
*/
/*

        // compute d parameter using equation 2
        double d = dot(N, A);

        // compute t (equation 3)
        double t = (dot(N, r.origin()) + d) / NdotRayDirection;

        // check if the triangle is in behind the ray
        if (t < 0)
            //return false; // the triangle is behind
            continue;

        // compute the intersection point using equation 1
        vec3 P = r.origin() + t * r.direction();


        // Step 2: inside-outside test ---------------------------------------------------------------------------------
        vec3 perp; // vector perpendicular to triangle's plane

        // edge 0
        vec3 edge0 = B - A;
        vec3 vp0 = P - A;
        perp = cross(edge0, vp0);
        if (dot(N, perp) < 0)
            //return false; // P is on the right side
            continue;

        // edge 1
        vec3 edge1 = C - B;
        vec3 vp1 = P - B;
        perp = cross(edge1, vp1);
        double u = perp.length() / area2;
        if (dot(N, perp) < 0)
            //return false; // P is on the right side
            continue;

        // edge 2
        vec3 edge2 = A - C;
        vec3 vp2 = P - C;
        perp = cross(edge2, vp2);
        double v = C.length() / area2;
        if (dot(N, perp) < 0)
            //return false; // P is on the right side;
            continue;

        result = vec3((*it).material.red, (*it).material.green, (*it).material.blue);

        //u /= denom;
        //v /= denom;

        return true; // this ray hits the triangle*/

    }

    if(lowestT == 99999) return -1;

    return lowestT;
}

std::ostream& operator<<(std::ostream &strm, const Triangles &t) {
    return strm << "Triangles( transformation: " << t.transformation << " )";
}
