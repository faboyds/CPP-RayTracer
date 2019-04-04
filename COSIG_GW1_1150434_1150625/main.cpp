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
#define EPSILON 0.0001

Image image;
Camera camera;
std::vector<Material> materials;
std::vector<Transformation> transformations;
std::vector<Light> lights;
std::vector<SceneObject *> objects;
std::string outputFile;

vec3 calculate_normal(vec3 unit_normal, double transposed_inverted_matrix[4][4]) {
    vec3 normal;

    tmutl::identityMatrix();
	tmutl::multiply3(transposed_inverted_matrix);
	tmutl::multiply1(unit_normal.e, normal.e);

	normal.e[3] = 0;

	return normal;
}

vec3 calculate_point(vec3 pointAtObjectReferential, double transformationMatrix[4][4]) {
	tmutl::identityMatrix();
	tmutl::multiply3(transformationMatrix);

	double auxMatrix[4][1];

	auxMatrix[0][0] = pointAtObjectReferential.x();
	auxMatrix[1][0] = pointAtObjectReferential.y();
	auxMatrix[2][0] = pointAtObjectReferential.z();
	auxMatrix[3][0] = 1;
	tmutl::multiply4x4b4x1(auxMatrix);

	vec3 point;

	point.e[0] = tmutl::transformMatrix[0][0];
	point.e[1] = tmutl::transformMatrix[1][0];
	point.e[2] = tmutl::transformMatrix[2][0];

	return point;
}

vec3 color(ray& r, int level) {

	double lowestT = 99999;
	SceneObject* hittedObject = nullptr;
	vec3 normal;
	Material material;
	vec3 point;

	vec3 finalColor = vec3(image.red, image.green, image.blue);

	for (std::vector<SceneObject *>::iterator it = objects.begin(); it != objects.end(); ++it) {

	    vec3 tempPoint;
		ray tempRay = r;

		// transforms ray to object referential
		tempRay.transform((*it)->transformation.inverseMatrix);

		// tries to hit object
		vec3 tempNormal = vec3(0, 0, 0);

		double t = -1;
		Material tempMaterial;

		if(Triangles* triangles = dynamic_cast<Triangles*>(*it)) {
			t = (*triangles).hit_object(tempRay, tempNormal, tempMaterial); // in Triangles object, the material differs between the object triangles
		} else {
			tempMaterial = (*it)->material;
			t = (*it)->hit_object(tempRay, tempNormal);
		}

		if(t < EPSILON) {
			continue;
		}

		vec3 pointAtObjectReferential = tempRay.point_at_parameter(t);
        tempPoint = calculate_point(pointAtObjectReferential, (*it)->transformation.matrix);

        // calculates world t
        t = r.t_to_point(tempPoint);

        // checks if t is the nearest t
		if(t < lowestT) {
			lowestT = t;
			hittedObject = (*it);
			normal = vec3(tempNormal.x(), tempNormal.y(), tempNormal.z());
			material = Material(tempMaterial.red, tempMaterial.green, tempMaterial.blue,
					tempMaterial.ambient, tempMaterial.diffuse, tempMaterial.reflection, tempMaterial.refractionCoefficient, tempMaterial.refractionIndex);

			point = vec3(tempPoint.x(), tempPoint.y(), tempPoint.z());
		}
	}

	// if any object was hitted
	if (lowestT < 99999) {

		// calculate normal
		normal = unit_vector(calculate_normal(normal, hittedObject->transformation.transposedInvertMatrix));

		// initialize tempColor
		vec3 tempColor = vec3(0, 0, 0);
		vec3 materialColor = vec3(material.red, material.green, material.blue);

		// iterate all lights
		for (std::vector<Light>::iterator lightIterator = lights.begin();
			 lightIterator != lights.end(); ++lightIterator) {

            vec3 lightColor = vec3((*lightIterator).red, (*lightIterator).green, (*lightIterator).blue);

            //calculate light position
            vec3 lightCenter;
            vec3 tempLightCenter = vec3(0, 0, 0);
            tempLightCenter.e[3] = 1;
            tmutl::identityMatrix();
            tmutl::multiply3((*lightIterator).transformation.matrix);
            tmutl::multiply1(tempLightCenter.e, lightCenter.e);
            lightCenter.e[3] = 1;

            // AMBIENT CONTRIBUTION
            tempColor += lightColor * materialColor * material.ambient;

            // DIFFUSE CONTRIBUTION
            double Llength = (lightCenter - point).length(); // vector L length
            ray rayPointToLight = ray(point, unit_vector(lightCenter - point)); // vector L normalize

            bool isInShadow = false;

            for (std::vector<SceneObject *>::iterator objectIt = objects.begin();
                 objectIt != objects.end(); ++objectIt) {

                double t;

                ray tempRay = rayPointToLight;
                vec3 tempPoint;

                // transforms ray to object referential
                tempRay.transform((*objectIt)->transformation.inverseMatrix);

                if (Triangles *triangles = dynamic_cast<Triangles *>(*objectIt)) {
                    t = (*triangles).hit_object(tempRay);
                } else {
                    t = (*objectIt)->hit_object(tempRay);
                }

                if (t < EPSILON) {
                    continue;
                }

                vec3 pointAtObjectReferential = tempRay.point_at_parameter(t);
                tempPoint = calculate_point(pointAtObjectReferential, (*objectIt)->transformation.matrix);

                // calculates world t
                t = rayPointToLight.t_to_point(tempPoint);

                if (t < Llength) {
                    isInShadow = true;
                    break;
                }
            }

            if (!isInShadow) {
                double d = dot(rayPointToLight.direction(), normal);
                if (d > 0) {
                    tempColor += lightColor * materialColor * material.diffuse * (d);
                }
            }

            if (level > 0) {
                //SPECULAR CONTRIBUTION

                if (material.reflection > 0) {

                    ray reflectedRay = ray(point, unit_vector(r.direction() - 2 * dot(r.direction(), normal) * normal));
                    vec3 reflectedResult = color(reflectedRay, level - 1);

                    tempColor += materialColor * material.reflection * reflectedResult;
                }

                if (material.refractionCoefficient > 0) {

                    vec3 refractedDirection;
                    double dt = dot(r.direction(), normal);
                    double n = material.refractionIndex;

                    double sinal = -1;

                    if(dt < 0) {
                        n = 1/n;
                        sinal = -sinal;
                        dt = -dt;
                    }

                    double discriminant = 1.0 - n * n * (1.0 - dt * dt);

                    refractedDirection = (n * r.direction()) + sinal*(n * dt - sqrt(discriminant)) * normal;

                    ray refractedRay = ray(point + EPSILON * r.direction(), unit_vector(refractedDirection));
                    vec3 refractedResult = color(refractedRay, level - 1);

                    tempColor += materialColor * material.refractionCoefficient * refractedResult;
                }
            }
        }

		// updates color with new values
		finalColor.e[0] = tempColor.e[0];
		finalColor.e[1] = tempColor.e[1];
		finalColor.e[2] = tempColor.e[2];
	}

	//background
	return finalColor;
}

void export_image() {
    //std::ofstream outfile("result.ppm");
    std::ofstream outfile(outputFile);

	outfile << "P3\n" << image.width << " " << image.height << "\n255\n";

	double height = 2 * (camera.distance * tan((camera.field_of_view/2) * (PI/180)));
	double width = height*image.width/image.height;
	int aa = 4;

	vec3 lower_left_corner(-width/2, -height/2, -camera.distance);
	vec3 horizontal(width, 0.0, 0.0);
	vec3 vertical(0.0, height, 0.0);
    vec3 origin(0.0, 0.0, camera.distance);

	vec3 col(0, 0, 0);

	for (int j = image.height - 1; j >= 0; j--) {
		for (int i = 0; i < image.width; i++) {

			for (int s = 0; s < aa; s++) {
				double rand_num = ((double)rand() / (RAND_MAX)); //random number between 0 and 1

				//u and v are coordinates of the pixel in the image, (u,v).
				double u = (i + rand_num) / image.width;
				double v = (j + rand_num) / image.height;


				//ray is p(t) = A + t*B, A being the origin and B being the direction
				ray r(origin, unit_vector(lower_left_corner + (u * horizontal) + (v * vertical)));

				col += color(r, 2);
			}
			col /= double(aa);

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
