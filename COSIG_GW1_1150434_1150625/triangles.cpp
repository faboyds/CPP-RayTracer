//
//  triangles.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "triangles.hpp"
#include "ray.hpp"

Triangles::Triangles(Transformation transformation,
                     std::vector<Triangle> triangles): SceneObject(transformation), triangles(triangles)
{
}

//TODO missing implementation
inline bool Triangles::hit_object(const ray& r) {
	return false;
}

std::ostream& operator<<(std::ostream &strm, const Triangles &t) {
    return strm << "Triangles( transformation: " << t.transformation << " )";
}
