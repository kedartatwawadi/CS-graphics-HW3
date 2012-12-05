/*
 * transformations.h
 *
 *  Created on: Sep 22, 2012
 *      Author: ayesha, kedar
 */

#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_

#include "matrix_t.h"
#include "vector_t.h"
#include "math_utility.h"

matrix_t WCS2VCS(vector_t E, vector_t A, vector_t up);
matrix_t VCS2CCS(double L, double R, double T, double B, double N, double F);
vector_t CCS2NDCS(matrix_t matrix);
vector_t NDCS2DCS(vector_t vector, int Lw, int Rw, int Tw, int Bw);
matrix_t VCS2NDCSOrtho(double L, double R, double T, double B, double N, double F);
matrix_t VCS2WCS(vector_t E, vector_t A, vector_t up);

#endif /* TRANSFORMATIONS_H_ */
