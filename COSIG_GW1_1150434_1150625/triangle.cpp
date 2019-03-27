//
//  triangle.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 21/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "triangle.hpp"

Triangle::Triangle(Material material, std::vector<Vertex> vertices): material(material), vertices(vertices)
{
}

void Triangle::buildNormalVector() {
    vec3 A = vec3(vertices[0].x, vertices[0].y, vertices[0].z);
    vec3 B = vec3(vertices[1].x, vertices[1].y, vertices[1].z);
    vec3 C = vec3(vertices[2].x, vertices[2].y, vertices[2].z);

    // compute plane's normal
    vec3 AB = B - A;
    vec3 AC = C - A;
    vec3 N = cross(AB, AC);
    N.make_unit_vector();

    normalVector = N;
}

std::ostream& operator<<(std::ostream &strm, const Triangle &t) {
    return strm << "Triangle( material: " << t.material << " )";
}
