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

std::ostream& operator<<(std::ostream &strm, const Triangle &t) {
    return strm << "Triangle( material: " << t.material << " )";
}
