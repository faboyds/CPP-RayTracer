#ifndef RAYH
#define RAYH
#include "vec3.hpp"
#include "transformation_utils.hpp"
/*
To help understand better what an array is in this context, think of it as as a function p(t) = A + t*B. 
Here p is a 3D position along a line in 3D. A is the ray origin and B is the ray direction. A different t means a different position along the ray.
The point_at_parameter function represents this function precisely. 
*/
class ray
{
    public:
        ray() {}
        ray(const vec3& a, const vec3& b) { A = a; B = b; A[3] = 1; B[3] = 0; }
        vec3 origin() const       { return A; }
        vec3 direction() const    { return B; }
        vec3 point_at_parameter(float t) const { return A + t*B; }
        double t_to_point(vec3 point) const { return ((point - A)/B).length(); }

		inline void transform(double matrix[4][4]) {

			double auxMatrix[4][1];

			//transform origin point -----------------------------------------------------------------------------------
			tmutl::identityMatrix();
			tmutl::multiply3(matrix);

			//convert origin point into matrix to multiply with transformation's matrix
			auxMatrix[0][0] = A.x();
			auxMatrix[1][0] = A.y();
			auxMatrix[2][0] = A.z();
			auxMatrix[3][0] = A.w();
			tmutl::multiply4x4b4x1(auxMatrix);

			A.e[0] = tmutl::transformMatrix[0][0];
			A.e[1] = tmutl::transformMatrix[1][0];
			A.e[2] = tmutl::transformMatrix[2][0];

			//transform direction vector -------------------------------------------------------------------------------
			tmutl::identityMatrix();
			tmutl::multiply3(matrix);

			//convert direction vector into matrix to multiply with transformation's matrix
			auxMatrix[0][0] = B.x();
			auxMatrix[1][0] = B.y();
			auxMatrix[2][0] = B.z();
			auxMatrix[3][0] = B.w();
			tmutl::multiply4x4b4x1(auxMatrix);

			B.e[0] = tmutl::transformMatrix[0][0];
			B.e[1] = tmutl::transformMatrix[1][0];
			B.e[2] = tmutl::transformMatrix[2][0];
			B.make_unit_vector();


			//std::cout << "  " << tmutl::transformMatrix[0][0] << "   " << tmutl::transformMatrix[0][1] << "   " << tmutl::transformMatrix[0][2] << "\n";
		}


		//Ray origin
		vec3 A;

		//Ray direction
        vec3 B;
};

#endif 


