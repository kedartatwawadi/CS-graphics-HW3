/*
 * vector_t.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: ayesha, kedar
 */

#include "vector_t.h"

vector_t::vector_t() {
	// TODO Auto-generated constructor stub
}

vector_t::vector_t(double x, double y, double z) {
	X = x;
	Y = y;
	Z = z;
}

double vector_t::getX() {
	return X;
}

void vector_t::setX(double x) {
	X = x;
}

double vector_t::getY() {
	return Y;
}

void vector_t::setY(double y) {
	Y = y;
}

double vector_t::getZ() {
	return Z;
}

void vector_t::setZ(double z) {
	Z = z;
}
