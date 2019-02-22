//
//  sphere.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "sphere.hpp"

Sphere::Sphere(Transformation transformation, Material material): SceneObject(transformation, material)
{
}

std::ostream& operator<<(std::ostream &strm, const Sphere &s) {
    return strm << "Sphere( transformation: " << s.transformation << ", material: " << s.material << " )";
}
