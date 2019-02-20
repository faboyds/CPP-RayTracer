//
//  main.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <algorithm>
#include <cctype>
#include <locale>

#include <vector>

#include "material.hpp"
#include "transformation.hpp"
#include "camera.hpp"

std::ifstream testSceneFile("../resources/test_scene.txt");

std::vector<Material> materials;
std::vector<Transformation> transformations;

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
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}

void importScene() {
    
    std::string line;

    while (std::getline(testSceneFile, line))
    {
        trim(line);

        if(line.compare("Image") == 0) {
            std::cout << line << "\n";
        }
        
        if(line.compare("Transformation") == 0) {
            
            std::getline(testSceneFile, line); //read '{'

            Transformation t;
            
            while (std::getline(testSceneFile, line) && line.find("}") == std::string::npos) {
                
                trim(line);
                
                if(line.find("T") != std::string::npos) {
                    std::vector<std::string> translate = split(line, ' '); //string format is T <x> <y> <z>, thus vector is = ['T', <x>, <y>, <z>]
                    
                    double x = std::atof(translate[1].c_str());
                    double y = std::atof(translate[2].c_str());
                    double z = std::atof(translate[3].c_str());
                    
                    t.x = x;
                    t.y = y;
                    t.z = z;
                }
                
                if(line.find("S") != std::string::npos) {
                    std::vector<std::string> scale = split(line, ' '); //string format is S <x> <y> <z>, thus vector is = ['S', <x>, <y>, <z>]
                    
                    double x = std::atof(scale[1].c_str());
                    double y = std::atof(scale[2].c_str());
                    double z = std::atof(scale[3].c_str());
                    
                    t.scaleX = x;
                    t.scaleY = y;
                    t.scaleZ = z;
                }
                
                if(line.find("Rx") != std::string::npos) {
                    std::vector<std::string> rotationX = split(line, ' '); //string format is Rx <x>, thus vector is = ['Rx', <x>]
                    
                    double x = std::atof(rotationX[1].c_str());
                    
                    t.rotationX = x;
                }
                
                if(line.find("Ry") != std::string::npos) {
                    std::vector<std::string> rotationY = split(line, ' '); //string format is Ry <y>, thus vector is = ['Ry', <y>]
                    
                    double y = std::atof(rotationY[1].c_str());
                    
                    t.rotationY = y;
                }
                
                if(line.find("Rz") != std::string::npos) {
                    std::vector<std::string> rotationZ = split(line, ' '); //string format is Rz <z>, thus vector is = ['Rz', <z>]
                    
                    double z = std::atof(rotationZ[1].c_str());
                    
                    t.rotationZ = z;
                }
            }
            
            std::cout << t << std::endl;
            transformations.push_back(t);
        }
        
        if(line.compare("Material") == 0) {
            
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
        
        if(line.compare("Camera") == 0) {

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
			Camera c(transformations[index], distance_double, field_of_view_double);
			std::cout << c << std::endl;

			std::getline(testSceneFile, line); //read '}'
        }
        
        if(line.compare("Light") == 0) {
            std::cout << line << "\n";
        }
        
        if(line.compare("Sphere") == 0) {
            std::cout << line << "\n";
        }
        
        if(line.compare("Box") == 0) {
            std::cout << line << "\n";
        }
        
        if(line.compare("Triangles") == 0) {
            std::cout << line << "\n";
        }
    }
}

int main(int argc, const char * argv[]) {
    importScene();
    
	system("pause");

    return 0;
}
