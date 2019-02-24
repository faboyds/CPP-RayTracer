#ifndef RAYH
#define RAYH
#include "vec3.hpp"

/*
To help understand better what an array is in this context, think of it as as a function p(t) = A + t*B. 
Here p is a 3D position along a line in 3D. A is the ray origin and B is the ray direction. A different t means a different position along the ray.
The point_at_parameter function represents this function precisely. 
*/
class ray
{
    public:
        ray() {}
        ray(const vec3& a, const vec3& b) { A = a; B = b; }  
        vec3 origin() const       { return A; }
        vec3 direction() const    { return B; }
        vec3 point_at_parameter(float t) const { return A + t*B; }

		//Ray origin
		vec3 A;

		//Ray direction
        vec3 B;
};

#endif 


