/*
 * vector_t.h
 *
 *  Created on: Sep 22, 2012
 *      Author: ayesha, kedar
 */

#ifndef VECTOR_T_H_
#define VECTOR_T_H_

class vector_t {
public:
	vector_t();
	vector_t(double x, double y, double z);

	double getX();
	void setX(double x);

	double getY();
	void setY(double y);

	double getZ();
	void setZ(double z);

private:
	double X;
	double Y;
	double Z;
};

#endif /* VECTOR_T_H_ */
