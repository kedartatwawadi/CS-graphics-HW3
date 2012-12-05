/*
(a) Must have a private pointer to a common framebuffer store object
as a data member, have methods to set and get this pointer.
(b) Must implement in a draw line method an all integer version of
Bresenham line drawing that works in any octant.
(c) A put pixel method that can turn on/off a pixel in the frame-
buffer store at position (x,y) by calling methods from the frame-
buffer store class.
*/


/*
 * \file rasterizer_t.h
 *
 *  Created on: Aug 11, 2012
 *      Author: ayesha, kedar
 */

#ifndef RASTERIZER_T_H_
#define RASTERIZER_T_H_
#include "drawing_3d_t.h"
#include "framebuffer_t.h"
#include "color_t.h"
#include "line_3d_t.h"

class rasterizer_t {
public:

	// rasterizer_t  default constructor
	rasterizer_t();
		
	// rasterizer_t constructor
	rasterizer_t(drawing_3d_t &draw1 , framebuffer_t &buffer1);
		
	// sets a value to pixel with coordinates <x,y> in the common frambuffer
	void putPixel(int x,int y,color_t value);
	
	// return the value of pixel (x,y)
	color_t getPixel(int x, int y);
		
	// Rasterizes a line
	void drawLine(line_3d_t line,color_t color);
		
	// rasterizes the complete drawing
	void rasterize();

	framebuffer_t getBuffer();
	void setBuffer(framebuffer_t buffer1);

	drawing_3d_t getCanvas();
	void setCanvas(drawing_3d_t canvas1);

private:
	drawing_3d_t canvas;
	// A pointer to the common drawing_t object
	framebuffer_t buffer; // A pointer to the common framebuffer object
};

#endif /* RASTERIZER_T_H_ */
