//
//  main.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>  

#include "ray.hpp"
#include "vec3.hpp"
#include "import_file.hpp"
#include "material.hpp"
#include "transformation.hpp"
#include "camera.hpp"
#include "image.hpp"
#include "light.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "triangles.hpp"
#include "vertex.hpp"
#include "sceneObject.hpp"

Image image;
Camera camera;
std::vector<Material> materials;
std::vector<Transformation> transformations;
std::vector<Light> lights;
std::vector<SceneObject> objects;

/*
Method that returns if the ray intersects the sphere. The discriminant can return either one, two or zero values. If it's one, it scraps the sphere. If two, it intersects the sphere in two points.
The method follows the sphere equation [(x-cx)*(x-cx) + (y-cy)*(y-cy) + (z-cz)*(z-cz)= R*R].
Adding the vector formula and expanding the equation to the left, we have the following quadration equation -> t*t*dot(B, B) + 2*t*dot(B,A-C) + dot(A-C,A-C) - R*R = 0.
Note that A and B and C refer to the origin of the vector, the direction of the vector and the center of the sphere, respectively.
*/
bool hit_sphere(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center;
	//parameters of the quadratic expression
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c; //discriminant from Bhaskara Formula
	return (discriminant > 0);
}

/*
For now, it returns the background color
*/
vec3 color(const ray& r) {
	//sphere (change here for the file)
	if (hit_sphere(vec3(0, 0, -1), 0.5, r)) {
		return vec3(1, 0, 0);
	}
	//background
	return vec3(image.red, image.green, image.blue);
}

void export_image() {
	std::ofstream outfile("result.ppm");

	outfile << "P3\n" << image.width << " " << image.height << "\n255\n";
	vec3 lower_left_corner(-(image.width/100), -(image.height/100), -1.0); //
	vec3 horizontal((image.width/100)*2, 0.0, 0.0);
	vec3 vertical(0.0, (image.height/100)*2, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	for (int j = image.height - 1; j >= 0; j--) {
		for (int i = 0; i < image.width; i++) {
			//u and v are coordinates of the pixel in the image, (u,v).
			float u = float(i) / float(image.width);
			float v = float(j) / float(image.height);

			//ray is p(t) = A + t*B, A being the origin and B being the direction
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);

			//for now, the scene only has a red sphere
			vec3 col = color(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			outfile << ir << " " << ig << " " << ib << std::endl;
		}
	}
	outfile.close();
	std::cout << "Finished exporting" << "\n";
}

int main(int argc, const char * argv[]) {
	//imports file
    import_file::importScene(image, materials, transformations, lights, objects, camera);

	//exports image
	export_image();

	//to press enter to leave
	getchar(); 

    return 0;
}
