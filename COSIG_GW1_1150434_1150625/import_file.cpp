#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <algorithm>
#include <cctype>
#include <locale>

#include <vector>

#include "import_file.hpp"

/*
Creates string stream from file. The file contains the information for the scene to be rendered in a specific format.
*/
std::ifstream testSceneFile("C:/Users/lucho/Documents/ISEP/ISEP/COSIG/RayTracer/COSIG_GW1_1150434_1150625/resources/test_scene.txt");
//std::ifstream testSceneFile("/Users/fabiolourenco/Projects/CPP-RayCasting/COSIG_GW1_1150434_1150625/resources/test_scene.txt");

/*
Often used to get lines such as 'Material' or '{'
*/
std::string line;

/*
Utils that allow trimming and splitting of vectors
*/
#pragma region Utils
// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}


std::vector<std::string> split(std::string str, char delimiter) {
	std::vector<std::string> internal;
	std::stringstream ss(str); // Turn the string into a stream.
	std::string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

#pragma endregion


namespace import_file {

	void get_image_information(Image &image) {
		std::getline(testSceneFile, line); //read '{'

		std::string size;
		std::string rgb;

		//read size
		std::getline(testSceneFile, size);
		trim(size);
		std::vector<std::string> sizeSplitted = split(size, ' ');
		double width = std::atof(sizeSplitted[0].c_str());
		double height = std::atof(sizeSplitted[1].c_str());

		//read RGB
		std::getline(testSceneFile, rgb);
		trim(rgb);
		std::vector<std::string> rgbSplitted = split(rgb, ' ');
		double red = std::atof(rgbSplitted[0].c_str());
		double green = std::atof(rgbSplitted[1].c_str());
		double blue = std::atof(rgbSplitted[2].c_str());

		image = Image(width, height, red, green, blue);
		std::cout << image << std::endl;

		std::getline(testSceneFile, line); //read '}'
	}
	void get_transformation_information(std::vector<Transformation> &transformations) {
		std::getline(testSceneFile, line); //read '{'

		Transformation t;

		while (std::getline(testSceneFile, line) && line.find("}") == std::string::npos) {

			trim(line);

			if (line.find("T") != std::string::npos) {
				std::vector<std::string> translate = split(line, ' '); //string format is T <x> <y> <z>, thus vector is = ['T', <x>, <y>, <z>]

				double x = std::atof(translate[1].c_str());
				double y = std::atof(translate[2].c_str());
				double z = std::atof(translate[3].c_str());

				t.x = x;
				t.y = y;
				t.z = z;
			}

			if (line.find("S") != std::string::npos) {
				std::vector<std::string> scale = split(line, ' '); //string format is S <x> <y> <z>, thus vector is = ['S', <x>, <y>, <z>]

				double x = std::atof(scale[1].c_str());
				double y = std::atof(scale[2].c_str());
				double z = std::atof(scale[3].c_str());

				t.scaleX = x;
				t.scaleY = y;
				t.scaleZ = z;
			}

			if (line.find("Rx") != std::string::npos) {
				std::vector<std::string> rotationX = split(line, ' '); //string format is Rx <x>, thus vector is = ['Rx', <x>]

				double x = std::atof(rotationX[1].c_str());

				t.rotationX = x;
			}

			if (line.find("Ry") != std::string::npos) {
				std::vector<std::string> rotationY = split(line, ' '); //string format is Ry <y>, thus vector is = ['Ry', <y>]

				double y = std::atof(rotationY[1].c_str());

				t.rotationY = y;
			}

			if (line.find("Rz") != std::string::npos) {
				std::vector<std::string> rotationZ = split(line, ' '); //string format is Rz <z>, thus vector is = ['Rz', <z>]

				double z = std::atof(rotationZ[1].c_str());

				t.rotationZ = z;
			}
		}

		std::cout << t << std::endl;
		transformations.push_back(t);
	}
	void get_materials_information(std::vector<Material> &materials) {
		std::getline(testSceneFile, line); //read '{'

		std::string rgb;
		std::string light;

		//read RGB
		std::getline(testSceneFile, rgb);
		trim(rgb);
		std::vector<std::string> rgbSplitted = split(rgb, ' ');
		double red = std::atof(rgbSplitted[0].c_str()); /*c_str is needed to convert string to const char* previously (the function requires it)*/
		double green = std::atof(rgbSplitted[1].c_str());
		double blue = std::atof(rgbSplitted[2].c_str());

		// read light
		std::getline(testSceneFile, light);
		trim(light);
		std::vector<std::string> lightSplitted = split(light, ' ');
		double ambient = std::atof(lightSplitted[0].c_str()); /*c_str is needed to convert string to const char* previously (the function requires it)*/
		double diffuse = std::atof(lightSplitted[1].c_str());
		double reflection = std::atof(lightSplitted[2].c_str());
		double refractionCoefficient = std::atof(lightSplitted[3].c_str());
		double refractionIndex = std::atof(lightSplitted[4].c_str());

		// create material and add to materials vector
		Material m(red, green, blue, ambient, diffuse, reflection, refractionCoefficient, refractionIndex);
		std::cout << m << std::endl;
		materials.push_back(m);

		std::getline(testSceneFile, line); //read '}'
	}
	void get_lights_information(std::vector<Light> &lights, std::vector<Transformation> &transformations) {
		std::getline(testSceneFile, line); //read '{'

		std::string transformationIndex;
		std::string rgb;

		//read transformation index
		std::getline(testSceneFile, transformationIndex);
		trim(transformationIndex);
		int transformationIndexValue = std::stoi(transformationIndex.c_str());

		//read RGB
		std::getline(testSceneFile, rgb);
		trim(rgb);
		std::vector<std::string> rgbSplitted = split(rgb, ' ');
		double red = std::atof(rgbSplitted[0].c_str());
		double green = std::atof(rgbSplitted[1].c_str());
		double blue = std::atof(rgbSplitted[2].c_str());

		// create light and add to materials vector
		Light l(transformations.at(transformationIndexValue), red, green, blue);
		std::cout << l << std::endl;
		lights.push_back(l);

		std::getline(testSceneFile, line); //read '}'
	}
	void get_camera_information(Camera &camera, std::vector<Transformation> &transformations) {
		std::getline(testSceneFile, line); //read '{'

		std::string transformation_index;
		std::string distance;
		std::string field_of_view;

		//read transformation
		std::getline(testSceneFile, transformation_index);
		trim(transformation_index);

		int index = std::stoi(transformation_index);

		// read distance
		std::getline(testSceneFile, distance);
		trim(distance);

		double distance_double = std::stod(distance);

		// read field_of_view
		std::getline(testSceneFile, field_of_view);
		trim(field_of_view);

		double field_of_view_double = std::stod(field_of_view);

		// create camera
		camera = Camera(transformations[index], distance_double, field_of_view_double);
		std::cout << camera << std::endl;

		std::getline(testSceneFile, line); //read '}'
	}
	void get_sphere_information(std::vector<SceneObject> &objects, std::vector<Transformation> &transformations, std::vector<Material> &materials) {
		std::getline(testSceneFile, line); //read '{'

		std::string transformationIndex;
		std::string materialIndex;

		//read transformation index
		std::getline(testSceneFile, transformationIndex);
		trim(transformationIndex);
		int transformationIndexValue = std::stoi(transformationIndex.c_str());

		//read material index
		std::getline(testSceneFile, materialIndex);
		trim(materialIndex);
		int materialIndexValue = std::stoi(materialIndex.c_str());

		// create sphere
		Sphere s(transformations.at(transformationIndexValue), materials.at(materialIndexValue));
		std::cout << s << std::endl;
		objects.push_back(s);

		std::getline(testSceneFile, line); //read '}'
	}
	void get_box_information(std::vector<SceneObject> &objects, std::vector<Transformation> &transformations, std::vector<Material> &materials) {
		std::getline(testSceneFile, line); //read '{'

		std::string transformationIndex;
		std::string materialIndex;

		//read transformation index
		std::getline(testSceneFile, transformationIndex);
		trim(transformationIndex);
		int transformationIndexValue = std::stoi(transformationIndex.c_str());

		//read material index
		std::getline(testSceneFile, materialIndex);
		trim(materialIndex);
		int materialIndexValue = std::stoi(materialIndex.c_str());

		// create box
		Box b(transformations.at(transformationIndexValue), materials.at(materialIndexValue));
		std::cout << b << std::endl;
		objects.push_back(b);

		std::getline(testSceneFile, line); //read '}'
	}
	void get_triangles_information(std::vector<SceneObject> &objects, std::vector<Transformation> &transformations, std::vector<Material> &materials) {
		std::getline(testSceneFile, line); //read '{'

		std::string transformationIndex;

		//read transformation index
		std::getline(testSceneFile, transformationIndex);
		trim(transformationIndex);
		int transformationIndexValue = std::stoi(transformationIndex.c_str());

		Triangles trianglesObject(transformations.at(transformationIndexValue), std::vector<Triangle>());

		while (std::getline(testSceneFile, line) && line.find("}") == std::string::npos) {
			//read material index ^

			std::string materialIndex = line;
			trim(materialIndex);
			int materialIndexValue = std::stoi(materialIndex.c_str());

			// create triangle
			Triangle triangle(materials.at(materialIndexValue), std::vector<Vertex>());

			for (int i = 0; i < 3; i++) {
				std::string position;

				//read position
				std::getline(testSceneFile, position);
				trim(position);
				std::vector<std::string> positionSplitted = split(position, ' ');
				double x = std::atof(positionSplitted[0].c_str());
				double y = std::atof(positionSplitted[1].c_str());
				double z = std::atof(positionSplitted[2].c_str());

				Vertex v(x, y, z);
				triangle.vertices.push_back(v);
			}

			std::cout << triangle << std::endl;
			trianglesObject.triangles.push_back(triangle);
		}

		std::cout << trianglesObject << std::endl;
		objects.push_back(trianglesObject);
	}

	void importScene(Image &image, 
		std::vector<Material> &materials, 
		std::vector<Transformation> &transformations,
		std::vector<Light> &lights,
		std::vector<SceneObject> &objects,
		Camera camera
	) {

		while (std::getline(testSceneFile, line))
		{
			trim(line);

			if (line.compare("Image") == 0) {
				get_image_information(image);
			}

			if (line.compare("Transformation") == 0) {
				get_transformation_information(transformations);
			}

			if (line.compare("Material") == 0) {
				get_materials_information(materials);
			}

			if (line.compare("Camera") == 0) {
				get_camera_information(camera, transformations);	
			}

			if (line.compare("Light") == 0) {
				get_lights_information(lights, transformations);
			}

			if (line.compare("Sphere") == 0) {
				get_sphere_information(objects, transformations, materials);
			}

			if (line.compare("Box") == 0) {
				get_box_information(objects, transformations, materials);
			}

			if (line.compare("Triangles") == 0) {
				get_triangles_information(objects, transformations, materials);
			}
		}
	}

}

