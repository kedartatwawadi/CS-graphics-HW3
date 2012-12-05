/*
 * \file color_t.h
 *
 *  Created on: Aug 18, 2012
 *      Author: ayesha, kedar
 */

#ifndef COLOR_T_H_
#define COLOR_T_H_

class color_t {
public:
	color_t();
	color_t(unsigned char red_component, unsigned char green_component, unsigned char blue_component);

	unsigned char getB();
	void setB(unsigned char blue_component);

	unsigned char getG();
	void setG(unsigned char green_component);

	unsigned char getR();
	void setR(unsigned char red_component);

private:
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

#endif /* COLOR_T_H_ */
