//
//  transformation.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "transformation.hpp"

#include <algorithm>    // std::copy
#include "transformation_utils.hpp"


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
    buildMatrix(matrix);
    buildInverseMatrix(matrix, inverseMatrix);
}

std::ostream& operator<<(std::ostream &strm, const Transformation &t) {
    return strm << "Transformation( x: " << t.x << ", y: " << t.y << ", z: " << t.z << ", rotationX: " << t.rotationX << ", rotationY: " << t.rotationY << ", rotationZ: " << t.rotationZ << ", scaleX: " << t.scaleX << ",  scaleY: " << t.scaleY << ",  scaleZ: " << t.scaleZ << " )";
}


// matrix [height][width]
void Transformation::buildMatrix(double mOut[4][4]) {
    identityMatrix();
    translate(x, y, z);
    rotateX(rotationX);
    rotateY(rotationY);
    rotateZ(rotationZ);
    scale(scaleX, scaleY, scaleZ);

    memcpy(mOut, transformMatrix, sizeof(transformMatrix));
}

void Transformation::buildInverseMatrix(double mIn[4][4], double mOut[4][4]) {

    double tempMIn[16];
    double tempMOut[16];

    memcpy(tempMIn, mIn, sizeof(tempMIn));
    memcpy(tempMOut, mOut, sizeof(tempMOut));

    inverse(tempMIn, tempMOut);

    memcpy(mIn, tempMIn, sizeof(tempMIn));
    memcpy(mOut, tempMOut, sizeof(tempMOut));
}
