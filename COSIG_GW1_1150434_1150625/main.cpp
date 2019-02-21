//
//  main.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "import_file.hpp"
#include <stdio.h>

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
std::vector<Material> materials;
std::vector<Transformation> transformations;
std::vector<Light> lights;
std::vector<SceneObject> objects;

int main(int argc, const char * argv[]) {
    import_file::importScene(image, materials, transformations, lights, objects);

	getchar(); //to press enter to leave

    return 0;
}
