//
//  transformation.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#pragma warning(disable : 4996)

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>

namespace tmutl {


    static double transformMatrix[4][4];

    static void multiply1(double const pointA[], double pointB[])
    {
        int i, j;

        for (i = 0; i < 4; i++)
            pointB[i] = 0.0;
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                pointB[i] += transformMatrix[i][j] * pointA[j];
    }

    static void multiply3(double matrixA[][4])
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


    static void multiply4x4b4x1(double matrixA[4][1])
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
            for (j = 0; j < 1; j++)
                for (k = 0; k < 4; k++) {
                    transformMatrix[i][j] += matrixB[i][k] * matrixA[k][j];
                    //std::cout << matrixB[i][k] << " * " << matrixA[k][j] << "\n";
                }

    }

    static void identityMatrix()
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

    static void translate(double x, double y, double z)
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

    static void rotateX(double a)
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

    static void rotateY(double a)
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

    static void rotateZ(double a)
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

    static void scale(double x, double y, double z)
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

    static bool inverse(const double m[16], double invOut[16]) {
        double inv[16], det;
        int i;

        inv[0] = m[5]  * m[10] * m[15] -
        m[5]  * m[11] * m[14] -
        m[9]  * m[6]  * m[15] +
        m[9]  * m[7]  * m[14] +
        m[13] * m[6]  * m[11] -
        m[13] * m[7]  * m[10];

        inv[4] = -m[4]  * m[10] * m[15] +
        m[4]  * m[11] * m[14] +
        m[8]  * m[6]  * m[15] -
        m[8]  * m[7]  * m[14] -
        m[12] * m[6]  * m[11] +
        m[12] * m[7]  * m[10];

        inv[8] = m[4]  * m[9] * m[15] -
        m[4]  * m[11] * m[13] -
        m[8]  * m[5] * m[15] +
        m[8]  * m[7] * m[13] +
        m[12] * m[5] * m[11] -
        m[12] * m[7] * m[9];

        inv[12] = -m[4]  * m[9] * m[14] +
        m[4]  * m[10] * m[13] +
        m[8]  * m[5] * m[14] -
        m[8]  * m[6] * m[13] -
        m[12] * m[5] * m[10] +
        m[12] * m[6] * m[9];

        inv[1] = -m[1]  * m[10] * m[15] +
        m[1]  * m[11] * m[14] +
        m[9]  * m[2] * m[15] -
        m[9]  * m[3] * m[14] -
        m[13] * m[2] * m[11] +
        m[13] * m[3] * m[10];

        inv[5] = m[0]  * m[10] * m[15] -
        m[0]  * m[11] * m[14] -
        m[8]  * m[2] * m[15] +
        m[8]  * m[3] * m[14] +
        m[12] * m[2] * m[11] -
        m[12] * m[3] * m[10];

        inv[9] = -m[0]  * m[9] * m[15] +
        m[0]  * m[11] * m[13] +
        m[8]  * m[1] * m[15] -
        m[8]  * m[3] * m[13] -
        m[12] * m[1] * m[11] +
        m[12] * m[3] * m[9];

        inv[13] = m[0]  * m[9] * m[14] -
        m[0]  * m[10] * m[13] -
        m[8]  * m[1] * m[14] +
        m[8]  * m[2] * m[13] +
        m[12] * m[1] * m[10] -
        m[12] * m[2] * m[9];

        inv[2] = m[1]  * m[6] * m[15] -
        m[1]  * m[7] * m[14] -
        m[5]  * m[2] * m[15] +
        m[5]  * m[3] * m[14] +
        m[13] * m[2] * m[7] -
        m[13] * m[3] * m[6];

        inv[6] = -m[0]  * m[6] * m[15] +
        m[0]  * m[7] * m[14] +
        m[4]  * m[2] * m[15] -
        m[4]  * m[3] * m[14] -
        m[12] * m[2] * m[7] +
        m[12] * m[3] * m[6];

        inv[10] = m[0]  * m[5] * m[15] -
        m[0]  * m[7] * m[13] -
        m[4]  * m[1] * m[15] +
        m[4]  * m[3] * m[13] +
        m[12] * m[1] * m[7] -
        m[12] * m[3] * m[5];

        inv[14] = -m[0]  * m[5] * m[14] +
        m[0]  * m[6] * m[13] +
        m[4]  * m[1] * m[14] -
        m[4]  * m[2] * m[13] -
        m[12] * m[1] * m[6] +
        m[12] * m[2] * m[5];

        inv[3] = -m[1] * m[6] * m[11] +
        m[1] * m[7] * m[10] +
        m[5] * m[2] * m[11] -
        m[5] * m[3] * m[10] -
        m[9] * m[2] * m[7] +
        m[9] * m[3] * m[6];

        inv[7] = m[0] * m[6] * m[11] -
        m[0] * m[7] * m[10] -
        m[4] * m[2] * m[11] +
        m[4] * m[3] * m[10] +
        m[8] * m[2] * m[7] -
        m[8] * m[3] * m[6];

        inv[11] = -m[0] * m[5] * m[11] +
        m[0] * m[7] * m[9] +
        m[4] * m[1] * m[11] -
        m[4] * m[3] * m[9] -
        m[8] * m[1] * m[7] +
        m[8] * m[3] * m[5];

        inv[15] = m[0] * m[5] * m[10] -
        m[0] * m[6] * m[9] -
        m[4] * m[1] * m[10] +
        m[4] * m[2] * m[9] +
        m[8] * m[1] * m[6] -
        m[8] * m[2] * m[5];

        det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

        if (det == 0)
            return false;

        det = 1.0 / det;

        for (i = 0; i < 16; i++)
            invOut[i] = inv[i] * det;

        return true;
    }

    static void process(void)
    {
        int m, i;
        double pointA[4], pointB[4];

        while (scanf("%d", &m) != EOF)
        {
            printf("%d\n", m);
            for (i = 0; i < 3; i++)
            {
                scanf("%lf %lf %lf", &pointA[0], &pointA[1], &pointA[2]);
                pointA[3] = 1.0;
                multiply1(pointA, pointB);
                printf("%lf %lf %lf\n", pointB[0] / pointB[3], pointB[1] / pointB[3], pointB[2] / pointB[3]);
            }
        }
    }

    static bool compareMatrices(double matrix1[4][4], double matrix2[4][4])
    {
        for (int i=0; i<4; ++i)
            for (int j=0; j<4; ++j)
                if(matrix1[i][j] != matrix2[i][j])
                    return false;
        return true;
    }

    static void print(){
        for(int x=0;x<4;x++)  // loop 4 times for four lines
        {
            for(int y=0;y<4;y++)  // loop for the three elements on the line
            {
                std::cout << transformMatrix[x][y] << " , ";  // display the current element out of the array
            }
            std::cout << std::endl;  // when the inner loop is done, go to a new line
        }
        std::cout << "\n";
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

};