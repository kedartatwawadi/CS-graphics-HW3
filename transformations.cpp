/*
 * transformations.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: ayesha, kedar
 */

#include "transformations.h"
#include <math.h>
#include <iostream>
#include "matrix_t.h"

using namespace std;

matrix_t WCS2VCS(vector_t E, vector_t A, vector_t up) {
	vector_t n_dash = vectorSubtract(E,A);
	double mod = vectorMod(n_dash);
	double n_x = n_dash.getX()/mod;
	double n_y = n_dash.getY()/mod;
	double n_z = n_dash.getZ()/mod;
	vector_t n(n_x,n_y,n_z);

	vector_t u_dash = crossProduct(up, n);
	mod = vectorMod(u_dash);
	double u_x = u_dash.getX()/mod;
	double u_y = u_dash.getY()/mod;
	double u_z = u_dash.getZ()/mod;
	vector_t u(u_x,u_y,u_z);

	vector_t v = crossProduct(n,u);
	double v_x = v.getX();
	double v_y = v.getY();
	double v_z = v.getZ();

	double e_x_dash = -dotProduct(u,E);
	double e_y_dash = -dotProduct(v,E);
	double e_z_dash = -dotProduct(n,E);


	double result_array[16] = {u_x, u_y, u_z, e_x_dash, v_x, v_y, v_z, e_y_dash, n_x, n_y, n_z, e_z_dash, 0, 0, 0, 1};
	matrix_t result(4,4,result_array);
	return result;
}

matrix_t VCS2CCS(double L, double R, double T, double B, double N, double F) {
	double result_array[16] = {(2*N/(R-L)), 0, ((R+L)/(R-L)), 0, 0, (2*N/(T-B)), ((T+B)/(T-B)), 0, 0, 0, -((F+N)/(F-N)), -(2*F*N/(F-N)), 0, 0, -1, 0};
	matrix_t result(4,4,result_array);

	return result;
}

vector_t CCS2NDCS(matrix_t matrix) {
	vector_t result = generateVector(matrix);
	return result;
}

vector_t NDCS2DCS(vector_t vector, int Lw, int Rw, int Tw, int Bw) {
	double x = vector.getX();
	double y = vector.getY();
	double z = vector.getZ();
	double x_dash = (x+1)*(Rw-Lw)/2 + Lw;
	double y_dash = (y+1)*(Tw-Bw)/2 + Bw;
	double z_dash = (z+1)/2;

	vector_t result(x_dash, y_dash, z_dash);
	return result;
}

matrix_t VCS2NDCSOrtho(double L, double R, double T, double B, double N, double F) {
	double result_array[16] = {(2/(R-L)), 0, 0, -((R+L)/(R-L)), 0, (2/(T-B)), 0, -((T+B)/(T-B)), 0, 0, -(2/(F-N)), -((F+N)/(F-N)), 0, 0, 0, 1};
	matrix_t result(4,4,result_array);

	return result;
}

matrix_t VCS2WCS(vector_t E, vector_t A, vector_t up){
	vector_t n_dash = vectorSubtract(E,A);
	double mod = vectorMod(n_dash);
	double n_x = n_dash.getX()/mod;
	double n_y = n_dash.getY()/mod;
	double n_z = n_dash.getZ()/mod;
	vector_t n(n_x,n_y,n_z);

	vector_t u_dash = crossProduct(up, n);
	mod = vectorMod(u_dash);
	double u_x = u_dash.getX()/mod;
	double u_y = u_dash.getY()/mod;
	double u_z = u_dash.getZ()/mod;
	vector_t u(u_x,u_y,u_z);

	vector_t v = crossProduct(n,u);
	double v_x = v.getX();
	double v_y = v.getY();
	double v_z = v.getZ();

	double e_x = E.getX() ;
	double e_y = E.getY();
	double e_z = E.getZ();

	double result_array[16] = {u_x, v_x, n_x, e_x, u_y, v_y, n_y, e_y, u_z, v_z, n_z, e_z, 0, 0, 0, 1};
	matrix_t result(4,4,result_array);

	return result;
}
