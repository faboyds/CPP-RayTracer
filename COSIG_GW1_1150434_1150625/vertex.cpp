//
//  vertex.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "vertex.hpp"

Vertex::Vertex(double x, double y, double z): x(x), y(y), z(z)
{
}

std::ostream& operator<<(std::ostream &strm, const Vertex &v) {
    return strm << "Vertex( x: " << v.x << ", y: " << v.y << ", z: " << v.z << " )";
}
