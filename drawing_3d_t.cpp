/*
 * drawing_3d_t.cpp
 *
 *  Created on: Sep 24, 2012
 *      Author: ayesha, kedar
 */

#include "drawing_3d_t.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "math_utility.h"
#include "matrix_t.h"
#include "transformations.h"

using namespace std;

drawing_3d_t::drawing_3d_t() {
	// TODO Auto-generated constructor stub
	windowWidth = 0;
	windowHeight = 0;
	numberOfLines = 0;
	//lineArray = NULL;
}

drawing_3d_t::drawing_3d_t(char* file_name) {
	char buffer1[2048];

	fstream fin;
	fin.open(file_name, ios::in);
	if (!fin) {
	cout << "\n\n*** That file does not exist ***\n";
	exit(0);
	// Exit program.
	}

	fin.getline(buffer1, 2048);
	readWindowDimensions(buffer1);//reading window dimensions

	fin.getline(buffer1, 2048);
	readE(buffer1);//reading window dimensions

	fin.getline(buffer1, 2048);
	readA(buffer1);//reading window dimensions

	fin.getline(buffer1, 2048);
	readUp(buffer1);//reading window dimensions

	fin.getline(buffer1, 2048);
	readFrustum(buffer1);//reading window dimensions

	fin.getline(buffer1, 2048);
	fin.getline(buffer1, 2048);
	readNumberOfLines(buffer1);//reading number of lines

	lineArray = (line_3d_t*) calloc(numberOfLines,sizeof(line_3d_t));
	for (int i = 0; i < numberOfLines-12; i++) 	{
		fin.getline(buffer1, 2048);
		char* pch = strtok (buffer1," ,");
		if(pch[0] == 'l') {
			readLine(i,buffer1);
		}
	}
	fin.close();

	addFrustum();
}

vector_t drawing_3d_t::getA() {
	return A;
}

void drawing_3d_t::setA(vector_t a) {
	A = a;
}

double drawing_3d_t::getB() {
	return B;
}

void drawing_3d_t::setB(double b) {
	B = b;
}

vector_t drawing_3d_t::getE() {
	return E;
}

void drawing_3d_t::setE(vector_t e) {
	E = e;
}

double drawing_3d_t::getF() {
	return F;
}

void drawing_3d_t::setF(double f) {
	F = f;
}

double drawing_3d_t::getL() {
	return L;
}

void drawing_3d_t::setL(double l) {
	L = l;
}

line_3d_t* drawing_3d_t::getLineArray() {
	return lineArray;
}

void drawing_3d_t::setLineArray(line_3d_t* line_array) {
	lineArray = line_array;
}

double drawing_3d_t::getN() {
	return N;
}

void drawing_3d_t::setN(double n) {
	N = n;
}

int drawing_3d_t::getNumberOfLines() {
	return numberOfLines;
}

void drawing_3d_t::setNumberOfLines(int number_of_lines) {
	numberOfLines = number_of_lines;
	lineArray = (line_3d_t*) calloc(number_of_lines, sizeof(line_3d_t));
}

double drawing_3d_t::getR() {
	return R;
}

void drawing_3d_t::setR(double r) {
	R = r;
}

double drawing_3d_t::getT() {
	return T;
}

void drawing_3d_t::setT(double t) {
	T = t;
}

vector_t drawing_3d_t::getUp() {
	return up;
}

void drawing_3d_t::setUp(vector_t up_vector) {
	up = up_vector;
}

int drawing_3d_t::getWindowHeight() {
	return windowHeight;
}

void drawing_3d_t::setWindowHeight(int window_height) {
	windowHeight = window_height;
}

int drawing_3d_t::getWindowWidth() {
	return windowWidth;
}

void drawing_3d_t::setWindowWidth(int window_width) {
	windowWidth = window_width;
}

void drawing_3d_t::readWindowDimensions(char* buffer) {
	char* pch;
	pch = strtok(buffer," ,");
	if (pch != NULL) {
		windowWidth = (int)atoi(pch);
		pch = strtok (NULL, " ,");
	}

	if (pch != NULL) {
		windowHeight = (int)atoi(pch);
		pch = strtok (NULL, " ,");
	}
}

void drawing_3d_t::readE(char* buffer) {
	char* pch;
	vector_t eye;
	pch = strtok(buffer," ,");
	if (pch != NULL) {
		eye.setX((double)atof(pch));
		pch = strtok (NULL, " ,");
	}

	if (pch != NULL) {
		eye.setY((double)atof(pch));
		pch = strtok (NULL, " ,");
	}

	if (pch != NULL) {
		eye.setZ((double)atof(pch));
		pch = strtok (NULL, " ,");
	}
	setE(eye);
}

void drawing_3d_t::readA(char* buffer) {
	char* pch;
	vector_t a;
	pch = strtok(buffer," ,");
	if (pch != NULL) {
		a.setX((double)atof(pch));
		pch = strtok (NULL, " ,");
	}

	if (pch != NULL) {
		a.setY((double)atof(pch));
		pch = strtok (NULL, " ,");
	}

	if (pch != NULL) {
		a.setZ((double)atof(pch));
		pch = strtok (NULL, " ,");
	}
	setA(a);
}

void drawing_3d_t::readUp(char* buffer) {
	char* pch;
	vector_t up_vector;
	pch = strtok(buffer," ,");
	if (pch != NULL) {
		up_vector.setX((double)atof(pch));
		pch = strtok (NULL, " ,");
	}

	if (pch != NULL) {
		up_vector.setY((double)atof(pch));
		pch = strtok (NULL, " ,");
	}

	if (pch != NULL) {
		up_vector.setZ((double)atof(pch));
		pch = strtok (NULL, " ,");
	}
	setUp(up_vector);
}

void drawing_3d_t::readFrustum(char* buffer) {
	char* pch;
	pch = strtok(buffer," ,");
	if (pch != NULL) {
		setL((double)atof(pch));
		pch = strtok (NULL, " ,");
	}

	if (pch != NULL) {
		setR((double)atof(pch));
		pch = strtok (NULL, " ,");
	}

	if (pch != NULL) {
		setT((double)atof(pch));
		pch = strtok (NULL, " ,");
	}

	if (pch != NULL) {
		setB((double)atof(pch));
		pch = strtok (NULL, " ,");
	}

	if (pch != NULL) {
		setN((double)atof(pch));
		pch = strtok (NULL, " ,");
	}

	if (pch != NULL) {
		setF((double)atof(pch));
		pch = strtok (NULL, " ,");
	}
}

void drawing_3d_t::readNumberOfLines(char* buffer)
{
	char* pch;
	pch = strtok(buffer," ,");
	if (pch != NULL) {
		numberOfLines = (int)atoi(pch);
		pch = strtok (NULL, " ,");
	}
	int numberOfFrustumLines = 12;
	numberOfLines = numberOfLines + numberOfFrustumLines;
}

void drawing_3d_t::readLine(int line_index, char* buffer) {
	char *pch = strtok (NULL, " ,");
	double value;
	vector_t vector;
	if (pch != NULL) {
		value = (double)atof(pch);
		vector.setX(value);
		pch = strtok (NULL, " ,");
	}
	if (pch != NULL) {
		value = (double)atof(pch);
		vector.setY(value);
		pch = strtok (NULL, " ,");
	}
	if (pch != NULL) {
		value = (double)atof(pch);
		vector.setZ(value);
		pch = strtok (NULL, " ,");
	}
	coordinates_3D_t coordinate;
	coordinate.setWcs(vector);
	lineArray[line_index].setV0(coordinate);

	if (pch != NULL) {
		value = (double)atof(pch);
		vector.setX(value);
		pch = strtok (NULL, " ,");
	}
	if (pch != NULL) {
		value = (double)atof(pch);
		vector.setY(value);
		pch = strtok (NULL, " ,");
	}
	if (pch != NULL) {
		value = (double)atof(pch);
		vector.setZ(value);
		pch = strtok (NULL, " ,");
	}
	coordinate.setWcs(vector);
	lineArray[line_index].setV1(coordinate);
}




vector_t drawing_3d_t::getWcsMin(){
	vector_t current_vector1,current_vector2;
	coordinates_3D_t current_cood1,current_cood2;
	int x_min = 1000000;
	int y_min = 1000000;
	int z_min = 1000000;
	for(int i = 0 ; i < numberOfLines ; i++){
		current_cood1 = lineArray[i].getV0();
		current_cood2 = lineArray[i].getV1();
		current_vector1 = current_cood1.getWcs();
		current_vector2 = current_cood2.getWcs();
		if(current_vector1.getX() < x_min) x_min = current_vector1.getX();
		if(current_vector2.getX() < x_min) x_min = current_vector2.getX();
		if(current_vector1.getY() < y_min) y_min = current_vector1.getY();
		if(current_vector2.getY() < y_min) y_min = current_vector2.getY();
		if(current_vector1.getZ() < z_min) z_min = current_vector1.getZ();
		if(current_vector2.getZ() < z_min) z_min = current_vector2.getZ();
	}
	vector_t min_vector(x_min, y_min, z_min);
	return min_vector;
}

vector_t drawing_3d_t::getWcsMax(){
	vector_t current_vector1,current_vector2;
	coordinates_3D_t current_cood1,current_cood2;
	int x_max = -1000000;
	int y_max = -1000000;
	int z_max = -1000000;
	for(int i = 0 ; i < numberOfLines ; i++){
		current_cood1 = lineArray[i].getV0();
		current_cood2 = lineArray[i].getV1();
		current_vector1 = current_cood1.getWcs();
		current_vector2 = current_cood2.getWcs();
		if(current_vector1.getX() > x_max) x_max = current_vector1.getX();
		if(current_vector2.getX() > x_max) x_max = current_vector2.getX();
		if(current_vector1.getY() > y_max) y_max = current_vector1.getY();
		if(current_vector2.getY() > y_max) y_max = current_vector2.getY();
		if(current_vector1.getZ() > z_max) z_max = current_vector1.getZ();
		if(current_vector2.getZ() > z_max) z_max = current_vector2.getZ();
	}
	vector_t max_vector(x_max, y_max, z_max);
	return max_vector;
}

void drawing_3d_t::addFrustum(){

double L_2 = L + 1;
double R_2 = R - 1;
double T_2 = T - 1;
double B_2 = B + 1;
double N_2 = N + 1;
double F_2 = F - 1;
double L_1 = (L_2*F_2)/N_2;
double R_1 = (R_2*F_2)/N_2;
double T_1 = (T_2*F_2)/N_2;
double B_1 = (B_2*F_2)/N_2;
matrix_t vcs_to_wcs = VCS2WCS(E,A,up);

vector_t frustum_p1(L_2,T_2,-N_2);
vector_t frustum_p2(L_2,B_2,-N_2);
vector_t frustum_p3(R_2,T_2,-N_2);
vector_t frustum_p4(R_2,B_2,-N_2);
vector_t frustum_p5(L_1,T_1,-F_2);
vector_t frustum_p6(L_1,B_1,-F_2);
vector_t frustum_p7(R_1,T_1,-F_2);
vector_t frustum_p8(R_1,B_1,-F_2);

addFrustumLine(frustum_p1,frustum_p2,vcs_to_wcs,numberOfLines-12);
addFrustumLine(frustum_p3,frustum_p4,vcs_to_wcs,numberOfLines-11);
addFrustumLine(frustum_p5,frustum_p6,vcs_to_wcs,numberOfLines-10);
addFrustumLine(frustum_p7,frustum_p8,vcs_to_wcs,numberOfLines-9);
addFrustumLine(frustum_p1,frustum_p3,vcs_to_wcs,numberOfLines-8);
addFrustumLine(frustum_p2,frustum_p4,vcs_to_wcs,numberOfLines-7);
addFrustumLine(frustum_p5,frustum_p7,vcs_to_wcs,numberOfLines-6);
addFrustumLine(frustum_p6,frustum_p8,vcs_to_wcs,numberOfLines-5);
addFrustumLine(frustum_p1,frustum_p5,vcs_to_wcs,numberOfLines-4);
addFrustumLine(frustum_p2,frustum_p6,vcs_to_wcs,numberOfLines-3);
addFrustumLine(frustum_p3,frustum_p7,vcs_to_wcs,numberOfLines-2);
addFrustumLine(frustum_p4,frustum_p8,vcs_to_wcs,numberOfLines-1);



}
void drawing_3d_t::addFrustumLine(vector_t v1,vector_t v2,matrix_t vcs_to_wcs,int line_index){
	matrix_t v1_homo = generateHomogeneousCoodMatrix(v1);
	matrix_t v2_homo = generateHomogeneousCoodMatrix(v2);
	matrix_t v1_homo_1 = matrixMultiply(vcs_to_wcs,v1_homo);
	matrix_t v2_homo_1 = matrixMultiply(vcs_to_wcs,v2_homo);
	v1 = generateVector(v1_homo_1);
	v2 = generateVector(v2_homo_1);
	line_3d_t line;
	line.setV0(v1);
	line.setV1(v2);
	lineArray[line_index] = line;
}
