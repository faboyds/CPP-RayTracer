//
//  sphere.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "sphere.hpp"
#include "vec3.hpp"
#include "ray.hpp"

Transformation transformation;
Material material;

Sphere::Sphere(Transformation transformation, Material material): SceneObject(transformation, material)
{
	this->transformation = transformation;
	this->material = material;
}

/*
Method that returns if the ray intersects the sphere. The discriminant can return either one, two or zero values. If it's one, it scraps the sphere. If two, it intersects the sphere in two points.
The method follows the sphere equation [(x-cx)*(x-cx) + (y-cy)*(y-cy) + (z-cz)*(z-cz)= R*R].
Adding the vector formula and expanding the equation to the left, we have the following quadration equation -> t*t*dot(B, B) + 2*t*dot(B,A-C) + dot(A-C,A-C) - R*R = 0.
Note that A and B and C refer to the origin of the vector, the direction of the vector and the center of the sphere, respectively.
*/
inline float Sphere::hit_object(const ray& r) {
	//this sphere is hardcoded (change here for the file)
	vec3 center = vec3(0, 0, -1);
    float radius = 0.5;

	vec3 oc = r.origin() - center;
	//parameters of the quadratic expression
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c; //discriminant from Bhaskara Formula

    if(discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
}

std::ostream& operator<<(std::ostream &strm, const Sphere &s) {
    return strm << "Sphere( transformation: " << s.transformation << ", material: " << s.material << " )";
}
