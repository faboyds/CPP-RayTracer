//
//  transformation.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "transformation.hpp"

Transformation::Transformation()
{
}

Transformation::Transformation(double x, double y, double z,
                               double rotationX, double rotationY, double rotationZ,
                               double scaleX, double scaleY, double scaleZ):
                                    x(x), y(y), z(z),
                                    rotationX(rotationX), rotationY(rotationY), rotationZ(rotationZ),
                                    scaleX(scaleX), scaleY(scaleY), scaleZ(scaleZ)
{
}

std::ostream& operator<<(std::ostream &strm, const Transformation &t) {
    return strm << "Transformation( x: " << t.x << ", y: " << t.y << ", z: " << t.z << ", rotationX: " << t.rotationX << ", rotationY: " << t.rotationY << ", rotationZ: " << t.rotationZ << ", scaleX: " << t.scaleX << ",  scaleY: " << t.scaleY << ",  scaleZ: " << t.scaleZ << " )";
}
