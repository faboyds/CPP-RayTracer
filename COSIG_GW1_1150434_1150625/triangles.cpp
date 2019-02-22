//
//  triangles.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "triangles.hpp"

Triangles::Triangles(Transformation transformation,
                     std::vector<Triangle> triangles): SceneObject(transformation), triangles(triangles)
{
}

std::ostream& operator<<(std::ostream &strm, const Triangles &t) {
    return strm << "Triangles( transformation: " << t.transformation << " )";
}
