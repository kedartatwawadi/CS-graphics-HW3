/*
 * math_utility.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: ayesha, kedar
 */

#include <iostream>
#include <math.h>
#include "math_utility.h"

using namespace std;

matrix_t matrixMultiply(matrix_t matrix1, matrix_t matrix2) {
	int r1 = matrix1.getNumRows();
	int c1 = matrix1.getNumColumns();
	int r2 = matrix2.getNumRows();
	int c2 = matrix2.getNumColumns();
	matrix_t result(r1, c2);
	if (r2 != c1) {
		cout<<"Matrix multiplication impossible!"<<endl;
	}

	else {
		double entry;
		for (int i = 0; i < r1; i++) {
			for (int j = 0; j < c2; j++) {
				entry = 0;
				for (int k = 0; k < c1; k++) {
					entry =entry + matrix1.getElement(i,k)*matrix2.getElement(k,j);
				}
				result.setElement(entry, i, j);
			}
		}

	}
	return result;
}

vector_t vectorSubtract(vector_t vector1, vector_t vector2) {
	double x = vector1.getX() - vector2.getX();
	double y = vector1.getY() - vector2.getY();
	double z = vector1.getZ() - vector2.getZ();

	vector_t result(x,y,z);
	return result;
}

double vectorMod(vector_t vector) {
	double x = vector.getX();
	double y = vector.getY();
	double z = vector.getZ();

	double mod_square = x*x + y*y + z*z;
	double mod = sqrt(mod_square);
	return mod;
}

double dotProduct(vector_t vector1, vector_t vector2) {
	double x1 = vector1.getX();
	double y1 = vector1.getY();
	double z1 = vector1.getZ();

	double x2 = vector2.getX();
	double y2 = vector2.getY();
	double z2 = vector2.getZ();

	double dot = x1*x2 + y1*y2 + z1*z2;
	return dot;
}

vector_t crossProduct(vector_t vector1, vector_t vector2) {
	double x1 = vector1.getX();
	double y1 = vector1.getY();
	double z1 = vector1.getZ();

	double x2 = vector2.getX();
	double y2 = vector2.getY();
	double z2 = vector2.getZ();

	double x = y1*z2 - y2*z1;
	double y = z1*x2 - z2*x1;
	double z = x1*y2 - x2*y1;

	vector_t cross(x,y,z);
	return cross;
}

matrix_t generateHomogeneousCoodMatrix(vector_t vector) {
	matrix_t result(4,1);

	double x = vector.getX();
	double y = vector.getY();
	double z = vector.getZ();

	result.setElement(x,0,0);
	result.setElement(y,1,0);
	result.setElement(z,2,0);
	result.setElement(1,3,0);

	return result;
}

vector_t generateVector(matrix_t matrix) {
	int num_of_rows = matrix.getNumRows();
	int num_of_columns = matrix.getNumColumns();

	vector_t result;
	if ((num_of_rows == 4) && (num_of_columns == 1)) {
		double x1 = matrix.getElement(0,0);
		double y1 = matrix.getElement(1,0);
		double z1 = matrix.getElement(2,0);
		double w1 = matrix.getElement(3,0);

		double x = x1/w1;
		double y = y1/w1;
		double z = z1/w1;

		result.setX(x);
		result.setY(y);
		result.setZ(z);

	}

	else {
		cout << "Matrix is not in homogeneous Cood System"<<endl;
	}
	return result;
}
