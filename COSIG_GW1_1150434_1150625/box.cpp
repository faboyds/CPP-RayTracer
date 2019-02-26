//
//  box.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "box.hpp"
#include "ray.hpp"

Box::Box(Transformation transformation, Material material): SceneObject(transformation, material)
{
}

//TODO missing implementation
inline float Box::hit_object(const ray& r) {
	return 0;
}

std::ostream& operator<<(std::ostream &strm, const Box &b) {
    return strm << "Box( transformation: " << b.transformation << ", material: " << b.material << " )";
}
