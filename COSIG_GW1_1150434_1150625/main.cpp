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
std::vector<SceneObject *> objects;
std::string outputFile;


/*
For now, it returns the background color and sphere
*/
vec3 color(const ray& r) {
	for (std::vector<SceneObject *>::iterator it = objects.begin(); it != objects.end(); ++it) {
        
        float t = (*it)->hit_object(r);
        
		if (t > 0.0) {
            vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
			return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1); //​N​ is a unit length vector– so each component is between -1 and 1) is to map each component to the interval from 0 to 1, and then map x/y/z to r/g/b
		}
	}
    
	//background
	return vec3(image.red, image.green, image.blue);
}

void export_image() {
    //std::ofstream outfile("result.ppm");
    std::ofstream outfile(outputFile);

	outfile << "P3\n" << image.width << " " << image.height << "\n255\n";
	vec3 lower_left_corner(-(image.width/100), -(image.height/100), -1.0); //
	vec3 horizontal((image.width/100)*2, 0.0, 0.0);
	vec3 vertical(0.0, (image.height/100)*2, 0.0);
	//vec3 origin(camera.transformation.x, camera.transformation.y, camera.transformation.z);
    vec3 origin(0, 0, 0);
    
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
    
    outputFile = argv[1];
    
	//imports file
    import_file::importScene(image, materials, transformations, lights, objects, camera);

	//exports image
	export_image();

	//to press enter to leave
	//getchar(); 

    return 0;
}
