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

std::ifstream testSceneFile("/Users/fabiolourenco/Documents/COSIG_GW1_1150434_1150625/COSIG_GW1_1150434_1150625/resources/test_scene.txt");

std::vector<Material> materials;

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
            std::cout << line << "\n";
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
            std::cout << line << "\n";
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

    return 0;
}
