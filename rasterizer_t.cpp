/*!
 * \file rasterizer_t.cpp
 *
 *  Created on: Aug 11, 2012
 *      Author: ayesha, kedar
 *  NOTE: CODE CREDITS:
 *  Code Credits: The Bresenham line rasterizer has been adapted from the sample code bresenham.cpp 
 *  provided by Prof. Parag Chaudhari (CSE IITB). The major part of the method drawLine has been adapted from this code:
 *  A link to the code is given below:
 *  http://www.cse.iitb.ac.in/~paragc/teaching/2012/cs675/demonotes.shtml#bresenham
 *  The code was modified to make it an all integer variant.
 *  homepage.smc.edu/kennedy_john/BRESENL.PDF
 */

#include "rasterizer_t.h"
#include "framebuffer_t.h"
#include <cmath>


rasterizer_t::rasterizer_t() 
{	

}

rasterizer_t::rasterizer_t(drawing_3d_t &draw1 , framebuffer_t &buffer1)
{
	canvas = draw1;
	buffer = buffer1;
}

void rasterizer_t::putPixel(int x,int y,color_t value)
{
	buffer.setPixelValue(x,y,value);
}

color_t rasterizer_t::getPixel(int x, int y)
{
	return buffer.getPixelValue(x, y);
}

void swap (int &x, int &y)
{
  int temp = x;
  x = y; y = temp;
}

//Generalized Bresenham (works for all lines)
void rasterizer_t::drawLine (line_3d_t line,color_t color)
{
	if(line.getClipFlag()==0)
	{
		
		
		int x0 = (int)line.getV0().getDcsClipped().getX();
		int y0 = (int)line.getV0().getDcsClipped().getY();
		int x1 = (int)line.getV1().getDcsClipped().getX();
		int y1 = (int)line.getV1().getDcsClipped().getY();
		bool steep = abs(y1 - y0) > abs(x1 - x0);
		if (steep)
		{
		  swap(x0, y0);
		  swap(x1, y1);
		}
		if (x0 > x1)
		{
			swap(x0, x1);
		    swap(y0, y1);
		}
		int deltax = x1 - x0;
		int deltay = abs(y1 - y0);	
		int error_dash = 0;
		int ystep;
		int y = y0;
		if (y0 < y1) ystep = 1;
		else if (y0>y1) ystep = -1;
		else ystep = 0;

		for (int x=x0; x < x1; x++)
		{

			if (steep){
            putPixel(y, x,color);
			}
			else {
			putPixel(x, y,color);
			}
			error_dash = error_dash + deltay;
			  
			if ((2*error_dash) >= deltax)
			{
			    y = y + ystep;
				error_dash = error_dash - deltax;
			}
		}
	}
}

void rasterizer_t::rasterize()
{
	int number_of_lines = canvas.getNumberOfLines();
	line_3d_t* line_array = canvas.getLineArray();
	line_3d_t line;

    buffer.clearPixelValueArray();
	for(int i = 0 ; i < number_of_lines-12 ; i++)
	{	
		line = line_array[i];
		color_t white(255,0,0);
		drawLine(line,white);
	}
	
	for(int i = number_of_lines-12 ; i < number_of_lines ; i++)
	{	
		line = line_array[i];
		color_t green(0,255,0);
		drawLine(line,green);
	}
	
	
}

bool compareColor(color_t color1, color_t color2)
{
	bool r = (color1.getR() == color2.getR());
	bool g = (color1.getG() == color2.getG());
	bool b = (color1.getB() == color2.getB());
	return (r&&g&&b);
}

framebuffer_t rasterizer_t::getBuffer() {
	return buffer;
}

void rasterizer_t::setBuffer(framebuffer_t buffer1) {
	buffer = buffer1;
}

drawing_3d_t rasterizer_t::getCanvas() {
	return canvas;
}

void rasterizer_t::setCanvas(drawing_3d_t canvas1) {
	canvas = canvas1;
}

