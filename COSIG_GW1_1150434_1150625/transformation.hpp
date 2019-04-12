//
//  transformation.hpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#ifndef transformation_hpp
#define transformation_hpp

#include <stdio.h>
#include <iostream>

#include "transformation_utils.hpp"

class Transformation {
    
public:
    double x = 0;
    double y = 0;
    double z = 0;
    
    double rotationX = 0;
    double rotationY = 0;
    double rotationZ = 0;
    
    double scaleX = 1;
    double scaleY = 1;
    double scaleZ = 1;

    double matrix[4][4];
    double inverseMatrix[4][4];
	double transposedInvertMatrix[4][4];

    Transformation();
    
    Transformation(
                   double x,
                   double y,
                   double z,
                   double rotationX,
                   double rotationY,
                   double rotationZ,
                   double scaleX,
                   double scaleY,
                   double scaleZ);
    
    friend std::ostream& operator<<(std::ostream&, const Transformation&);

    void buildMatrix(double mOut [4][4]);
    void buildInverseMatrix(double mIn[4][4], double mOut[4][4]);
	void buildTransposedInversedMatrix(double mIn[4][4], double mOut[4][4]);
};

#endif /* transformation_hpp */
