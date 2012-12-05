/*
 * drawing_3d_t.h
 *
 *  Created on: Sep 24, 2012
 *      Author: ayesha, kedar
 */

#ifndef DRAWING_3D_T_H_
#define DRAWING_3D_T_H_

#include <string.h>
#include <iostream>
#include "line_3d_t.h"
#include "vector_t.h"
#include "matrix_t.h"

using namespace std;

class drawing_3d_t {
public:
	drawing_3d_t();
	drawing_3d_t(char* file_name);

	vector_t getA();
	void setA(vector_t a);

	double getB() ;
	void setB(double b);

	vector_t getE();
	void setE(vector_t e);

	double getF();
	void setF(double f);

	double getL();
	void setL(double l);

	line_3d_t* getLineArray();
	void setLineArray(line_3d_t* line_array);

	double getN() ;
	void setN(double n);

	int getNumberOfLines();
	void setNumberOfLines(int number_of_lines);

	double getR();
	void setR(double r);

	double getT();
	void setT(double t);

	vector_t getUp();
	void setUp(vector_t up_vector);

	int getWindowHeight();
	void setWindowHeight(int window_height);

	int getWindowWidth();
	void setWindowWidth(int window_width);

	vector_t getWcsMin();
	vector_t getWcsMax();

	void readWindowDimensions(char* buffer);
	void readE(char* buffer);
	void readA(char* buffer);
	void readUp(char* buffer);
	void readFrustum(char* buffer);
	void addFrustum();
	void addFrustumLine(vector_t v1,vector_t v2,matrix_t vcs_to_wcs,int line_index);
	void readNumberOfLines(char* buffer);
	void readLine(int line_index, char* buffer);

private:
	int windowWidth; /// the window width
	int windowHeight; /// the window height
	vector_t E;
	vector_t A;
	vector_t up;
	double L;
	double R;
	double T;
	double B;
	double N;
	double F;
	int numberOfLines; /// the number of lines
	line_3d_t* lineArray; /// the array of line objects
};

#endif /* DRAWING_3D_T_H_ */
