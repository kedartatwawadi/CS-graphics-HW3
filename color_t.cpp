/*!
 * \file color_t.cpp
 *
 *  Created on: Aug 18, 2012
 *      Author: ayesha, kedar
 */

#include "color_t.h"

color_t::color_t() {
	// TODO Auto-generated constructor stub

}

color_t::color_t(unsigned char red_component, unsigned char green_component, unsigned char blue_component)
{
	r = red_component;
	g = green_component;
	b = blue_component;
}


unsigned char color_t::getB() {
		return b;
	}

	void color_t::setB(unsigned char blue_component) {
		b = blue_component;
	}

	unsigned char color_t::getG(){
		return g;
	}

	void color_t::setG(unsigned char green_component) {
		g = green_component;
	}

	unsigned char color_t::getR(){
		return r;
	}

	void color_t::setR(unsigned char red_component) {
		r = red_component;
	}


