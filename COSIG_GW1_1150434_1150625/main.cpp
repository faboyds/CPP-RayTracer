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

void export_image() {
	std::ofstream outfile("result.ppm");

	outfile << "P3\n" << image.width << " " << image.height << "\n255\n";
	for (int j = image.height - 1; j >= 0; j--) {
		for (int i = 0; i < image.width; i++) {
			float r = float(i) / float(image.width);
			float g = float(j) / float(image.height);
			float b = 0.2;
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);
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
