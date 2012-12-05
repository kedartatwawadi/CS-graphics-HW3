/*
 * coordinates_3D_t.cpp
 *
 *  Created on: Sep 23, 2012
 *      Author: ayesha, kedar
 */

#include "coordinates_3D_t.h"

coordinates_3D_t::coordinates_3D_t() {
	// TODO Auto-generated constructor stub
}

coordinates_3D_t::coordinates_3D_t(vector_t vector) {
	Wcs = vector;
}

vector_t coordinates_3D_t::getCcs() {
	return Ccs;
}

void coordinates_3D_t::setCcs(vector_t ccs) {
	Ccs = ccs;
}

vector_t coordinates_3D_t::getDcs() {
	return Dcs;
}

void coordinates_3D_t::setDcs(vector_t dcs) {
	Dcs = dcs;
}

vector_t coordinates_3D_t::getNdcs() {
	return Ndcs;
}

void coordinates_3D_t::setNdcs(vector_t ndcs) {
	Ndcs = ndcs;
}

vector_t coordinates_3D_t::getVcs() {
	return Vcs;
}

void coordinates_3D_t::setVcs(vector_t vcs) {
	Vcs = vcs;
}

vector_t coordinates_3D_t::getWcs() {
	return Wcs;
}

void coordinates_3D_t::setWcs(vector_t wcs) {
	Wcs = wcs;
}

vector_t coordinates_3D_t::getCcsClipped() {
	return CcsClipped;
}

void coordinates_3D_t::setCcsClipped(vector_t ccs_clipped) {
	CcsClipped = ccs_clipped;
}

vector_t coordinates_3D_t::getDcsClipped() {
	return DcsClipped;
}

void coordinates_3D_t::setDcsClipped(vector_t dcs_clipped) {
	DcsClipped = dcs_clipped;
}

vector_t coordinates_3D_t::getNdcsClipped() {
	return NdcsClipped;
}

void coordinates_3D_t::setNdcsClipped(vector_t ndcs_clipped) {
	NdcsClipped = ndcs_clipped;
}

double coordinates_3D_t::getWCcs(){
	return wCcs;
}
void coordinates_3D_t::setWCcs(double w_ccs) {
	wCcs = w_ccs;
}
