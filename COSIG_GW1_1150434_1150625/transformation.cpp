//
//  transformation.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "transformation.hpp"

#include <algorithm>    // std::copy


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
    tmutl utils = tmutl();

    utils.identityMatrix();
    utils.translate(x, y, z);
    utils.rotateX(rotationX);
    utils.rotateY(rotationY);
    utils.rotateZ(rotationZ);
    utils.scale(scaleX, scaleY, scaleZ);

    memcpy(mOut, utils.transformMatrix, sizeof(utils.transformMatrix));
}

void Transformation::buildInverseMatrix(double mIn[4][4], double mOut[4][4]) {
    tmutl utils = tmutl();

    double tempMIn[16];
    double tempMOut[16];

    memcpy(tempMIn, mIn, sizeof(tempMIn));
    memcpy(tempMOut, mOut, sizeof(tempMOut));

    utils.inverse(tempMIn, tempMOut);

    memcpy(mIn, tempMIn, sizeof(tempMIn));
    memcpy(mOut, tempMOut, sizeof(tempMOut));
}

void Transformation::buildTransposedInversedMatrix(double mIn[4][4], double mOut[4][4]) {

	double tempMatrix[4][4];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tempMatrix[j][i] = mIn[i][j];
		}
	}

	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mOut[i][j] = tempMatrix[i][j];
		}
	}

}
