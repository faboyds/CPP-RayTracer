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

    strm << "Transformation( matrix: \n";

    for(int x=0;x<4;x++)
    {
        for(int y=0;y<4;y++)
        {
            strm << t.matrix[x][y] << " , ";
        }
        strm << std::endl;
    }

    return strm << ")";
}


// matrix [height][width]
void Transformation::buildMatrix(double mOut[4][4]) {

    tmutl::identityMatrix();
    tmutl::translate(x, y, z);
    tmutl::rotateX(rotationX);
    tmutl::rotateY(rotationY);
    tmutl::rotateZ(rotationZ);
    tmutl::scale(scaleX, scaleY, scaleZ);

    memcpy(mOut, tmutl::transformMatrix, sizeof(tmutl::transformMatrix));
}

void Transformation::buildInverseMatrix(double mIn[4][4], double mOut[4][4]) {

    double tempMIn[16];
    double tempMOut[16];

    memcpy(tempMIn, mIn, sizeof(tempMIn));
    memcpy(tempMOut, mOut, sizeof(tempMOut));

    tmutl::inverse(tempMIn, tempMOut);

    memcpy(mIn, tempMIn, sizeof(tempMIn));
    memcpy(mOut, tempMOut, sizeof(tempMOut));
}
