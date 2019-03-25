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
#include <math.h>

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

#define PI 3.14159265

Image image;
Camera camera;
std::vector<Material> materials;
std::vector<Transformation> transformations;
std::vector<Light> lights;
std::vector<SceneObject *> objects;
std::string outputFile;


/*
For now, it returns the background color and sphere
*/
vec3 color(ray& r) {

	double lowestT = 99999;
	vec3 color = vec3(image.red, image.green, image.blue);

	for (std::vector<SceneObject *>::iterator it = objects.begin(); it != objects.end(); it++) {

		vec3 tempColor;
		ray tempRay = r;

		tempRay.transform((*it)->transformation.inverseMatrix);

        double t = (*it)->hit_object(tempRay, tempColor);

		tempRay.transform((*it)->transformation.matrix);

		if(t > 0 && t < lowestT) {
			lowestT = t;
			color.e[0] = tempColor.e[0];
			color.e[1] = tempColor.e[1];
			color.e[2] = tempColor.e[2];
        }
	}

	//background
	return color;
}

void export_image() {
    //std::ofstream outfile("result.ppm");
    std::ofstream outfile(outputFile);

	outfile << "P3\n" << image.width << " " << image.height << "\n255\n";

	double height = 2 * (camera.distance * tan((camera.field_of_view/2) * (PI/180)));
	double width = height*image.width/image.height;

	std::cout << height << "   " << width << "\n\n";

	vec3 lower_left_corner(-width/2, -height/2, -camera.distance);
	vec3 horizontal(width, 0.0, 0.0);
	vec3 vertical(0.0, height, 0.0);
    vec3 origin(0.0, 0.0, camera.distance);

	for (int j = image.height - 1; j >= 0; j--) {
		for (int i = 0; i < image.width; i++) {
			//u and v are coordinates of the pixel in the image, (u,v).
			double u = double(i+0.5) / image.width;
			double v = double(j+0.5) / image.height;

			//ray is p(t) = A + t*B, A being the origin and B being the direction
			ray r(origin, unit_vector(lower_left_corner + (u * horizontal) + (v * vertical)));

			if(j < 10 && i < 10) {
				std::cout << r.B.x() << "   " << r.B.y() << "   " << r.B.z() << "\n";
			}


			//for now, the scene only has a red sphere
			vec3 col = color(r);
			int ir = int(255*col[0]);
			int ig = int(255*col[1]);
			int ib = int(255*col[2]);
			outfile << ir << " " << ig << " " << ib << std::endl;
		}
	}

	outfile.close();
	std::cout << "Finished exporting" << "\n";
}

int main(int argc, const char * argv[]) {
    
    outputFile = argv[1];
    
	//imports file
    import_file::importScene(image, materials, transformations, lights, objects, camera);

	//exports image
	export_image();

	//to press enter to leave
	//getchar(); 

    return 0;
}
