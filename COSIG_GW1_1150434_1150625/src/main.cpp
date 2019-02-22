//
//  main.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "utils/import_file.hpp"
#include <stdio.h>

#include "model/material.hpp"
#include "model/transformation.hpp"
#include "model/camera.hpp"
#include "model/image.hpp"
#include "model/light.hpp"
#include "model/box.hpp"
#include "model/sphere.hpp"
#include "model/triangles.hpp"
#include "model/vertex.hpp"
#include "model/sceneObject.hpp"

Image image;
Camera camera;
std::vector<Material> materials;
std::vector<Transformation> transformations;
std::vector<Light> lights;
std::vector<SceneObject> objects;

int main(int argc, const char * argv[]) {
    import_file::importScene(image, materials, transformations, lights, objects, camera);

	getchar(); //to press enter to leave

    return 0;
}
