//
//  transformation.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>

double transformMatrix[4][4];

void multiply1(double pointA[], double pointB[])
{
    int i, j;
    
    for (i = 0; i < 4; i++)
        pointB[i] = 0.0;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            pointB[i] += transformMatrix[i][j] * pointA[j];
}

void multiply3(double matrixA[][4])
{
    int i, j, k;
    double matrixB[4][4];
    
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            matrixB[i][j] = transformMatrix[i][j];
            transformMatrix[i][j] = 0.0;
        }
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            for (k = 0; k < 4; k++)
                transformMatrix[i][j] += matrixB[i][k] * matrixA[k][j];
}

void identityMatrix()
{
    transformMatrix[0][0] = 1.0;
    transformMatrix[0][1] = 0.0;
    transformMatrix[0][2] = 0.0;
    transformMatrix[0][3] = 0.0;
    transformMatrix[1][0] = 0.0;
    transformMatrix[1][1] = 1.0;
    transformMatrix[1][2] = 0.0;
    transformMatrix[1][3] = 0.0;
    transformMatrix[2][0] = 0.0;
    transformMatrix[2][1] = 0.0;
    transformMatrix[2][2] = 1.0;
    transformMatrix[2][3] = 0.0;
    transformMatrix[3][0] = 0.0;
    transformMatrix[3][1] = 0.0;
    transformMatrix[3][2] = 0.0;
    transformMatrix[3][3] = 1.0;
}

void translate(double x, double y, double z)
{
    double translateMatrix[4][4];
    
    translateMatrix[0][0] = 1.0;
    translateMatrix[0][1] = 0.0;
    translateMatrix[0][2] = 0.0;
    translateMatrix[0][3] = x;
    translateMatrix[1][0] = 0.0;
    translateMatrix[1][1] = 1.0;
    translateMatrix[1][2] = 0.0;
    translateMatrix[1][3] = y;
    translateMatrix[2][0] = 0.0;
    translateMatrix[2][1] = 0.0;
    translateMatrix[2][2] = 1.0;
    translateMatrix[2][3] = z;
    translateMatrix[3][0] = 0.0;
    translateMatrix[3][1] = 0.0;
    translateMatrix[3][2] = 0.0;
    translateMatrix[3][3] = 1.0;
    multiply3(translateMatrix);
}

void rotateX(double a)
{
    double rotateXMatrix[4][4];
    
    a *= M_PI / 180.0;
    rotateXMatrix[0][0] = 1.0;
    rotateXMatrix[0][1] = 0.0;
    rotateXMatrix[0][2] = 0.0;
    rotateXMatrix[0][3] = 0.0;
    rotateXMatrix[1][0] = 0.0;
    rotateXMatrix[1][1] = cos(a);
    rotateXMatrix[1][2] = -sin(a);
    rotateXMatrix[1][3] = 0.0;
    rotateXMatrix[2][0] = 0.0;
    rotateXMatrix[2][1] = sin(a);
    rotateXMatrix[2][2] = cos(a);
    rotateXMatrix[2][3] = 0.0;
    rotateXMatrix[3][0] = 0.0;
    rotateXMatrix[3][1] = 0.0;
    rotateXMatrix[3][2] = 0.0;
    rotateXMatrix[3][3] = 1.0;
    multiply3(rotateXMatrix);
}

void rotateY(double a)
{
    double rotateYMatrix[4][4];
    
    a *= M_PI / 180.0;
    rotateYMatrix[0][0] = cos(a);
    rotateYMatrix[0][1] = 0.0;
    rotateYMatrix[0][2] = sin(a);
    rotateYMatrix[0][3] = 0.0;
    rotateYMatrix[1][0] = 0.0;
    rotateYMatrix[1][1] = 1.0;
    rotateYMatrix[1][2] = 0.0;
    rotateYMatrix[1][3] = 0.0;
    rotateYMatrix[2][0] = -sin(a);
    rotateYMatrix[2][1] = 0.0;
    rotateYMatrix[2][2] = cos(a);
    rotateYMatrix[2][3] = 0.0;
    rotateYMatrix[3][0] = 0.0;
    rotateYMatrix[3][1] = 0.0;
    rotateYMatrix[3][2] = 0.0;
    rotateYMatrix[3][3] = 1.0;
    multiply3(rotateYMatrix);
}

void rotateZ(double a)
{
    double rotateZMatrix[4][4];
    
    a *= M_PI / 180.0;
    rotateZMatrix[0][0] = cos(a);
    rotateZMatrix[0][1] = -sin(a);
    rotateZMatrix[0][2] = 0.0;
    rotateZMatrix[0][3] = 0.0;
    rotateZMatrix[1][0] = sin(a);
    rotateZMatrix[1][1] = cos(a);
    rotateZMatrix[1][2] = 0.0;
    rotateZMatrix[1][3] = 0.0;
    rotateZMatrix[2][0] = 0.0;
    rotateZMatrix[2][1] = 0.0;
    rotateZMatrix[2][2] = 1.0;
    rotateZMatrix[2][3] = 0.0;
    rotateZMatrix[3][0] = 0.0;
    rotateZMatrix[3][1] = 0.0;
    rotateZMatrix[3][2] = 0.0;
    rotateZMatrix[3][3] = 1.0;
    multiply3(rotateZMatrix);
}

void scale(double x, double y, double z)
{
    double scaleMatrix[4][4];
    
    scaleMatrix[0][0] = x;
    scaleMatrix[0][1] = 0.0;
    scaleMatrix[0][2] = 0.0;
    scaleMatrix[0][3] = 0.0;
    scaleMatrix[1][0] = 0.0;
    scaleMatrix[1][1] = y;
    scaleMatrix[1][2] = 0.0;
    scaleMatrix[1][3] = 0.0;
    scaleMatrix[2][0] = 0.0;
    scaleMatrix[2][1] = 0.0;
    scaleMatrix[2][2] = z;
    scaleMatrix[2][3] = 0.0;
    scaleMatrix[3][0] = 0.0;
    scaleMatrix[3][1] = 0.0;
    scaleMatrix[3][2] = 0.0;
    scaleMatrix[3][3] = 1.0;
    multiply3(scaleMatrix);
}

void process(void)
{
    int m, i;
    double pointA[4], pointB[4];
    
    while (scanf_s("%d", &m) != EOF)
    {
        printf("%d\n", m);
        for (i = 0; i < 3; i++)
        {
            scanf_s("%lf %lf %lf", &pointA[0], &pointA[1], &pointA[2]);
            pointA[3] = 1.0;
            multiply1(pointA, pointB);
            printf("%lf %lf %lf\n", pointB[0] / pointB[3], pointB[1] / pointB[3], pointB[2] / pointB[3]);
        }
    }
}

/*
void main(void)
{
    identityMatrix();
    translate(0.0, 0.0, -74.0);
    rotateX(-60.0);
    rotateZ(45.0);
    process();
}
 */
