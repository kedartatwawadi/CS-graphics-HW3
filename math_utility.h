/*
 * math_utility.h
 *
 *  Created on: Sep 22, 2012
 *      Author: ayesha, kedar
 */

#ifndef MATH_UTILITY_H_
#define MATH_UTILITY_H_

#include "matrix_t.h"
#include "vector_t.h"

matrix_t matrixMultiply(matrix_t matrix1, matrix_t matrix2);
vector_t vectorSubtract(vector_t vector1, vector_t vector2);
double vectorMod(vector_t vector);
double dotProduct(vector_t vector1, vector_t vector2);
vector_t crossProduct(vector_t vector1, vector_t vector2);
matrix_t generateHomogeneousCoodMatrix(vector_t vector);
vector_t generateVector(matrix_t matrix);

#endif /* MATH_UTILITY_H_ */
