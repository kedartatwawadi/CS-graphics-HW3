/*
 * line_3d_t.cpp
 *
 *  Created on: Sep 24, 2012
 *      Author: ayesha, kedar
 */

#include "line_3d_t.h"

line_3d_t::line_3d_t() {
	// TODO Auto-generated constructor stub
}

line_3d_t::line_3d_t(coordinates_3D_t v_0, coordinates_3D_t v_1) {
	v0 = v_0;
	v1 = v_1;
	clipFlag = 0;
}

int line_3d_t::getClipFlag() {
	return clipFlag;
}

void line_3d_t::setClipFlag(int flag) {
	clipFlag = flag;
}

coordinates_3D_t line_3d_t::getV0() {
	return v0;
}

void line_3d_t::setV0(coordinates_3D_t v_0) {
	v0 = v_0;
}

coordinates_3D_t line_3d_t::getV1() {
	return v1;
}

void line_3d_t::setV1(coordinates_3D_t v_1) {
	v1 = v_1;
}
