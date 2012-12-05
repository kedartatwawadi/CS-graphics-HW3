/*
 * framebuffer_t.cpp
 *
 *  Created on: Aug 7, 2012
 *      Author: ayesha, kedar
 */

#include "framebuffer_t.h"
#include <stdlib.h>

framebuffer_t::framebuffer_t()
{
	windowWidth = 0;
	windowHeight = 0;
	pixelValueArray = 0;
}

framebuffer_t::framebuffer_t(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	pixelArraySize = w*h*3;
	pixelValueArray = (unsigned char*) calloc(pixelArraySize,sizeof(unsigned char));
	stepSize = windowWidth*3;
}

void framebuffer_t::setFrameBuffer(int w, int h){
	windowWidth = w;
	windowHeight = h;
	pixelArraySize = w*h*3;
	pixelValueArray = (unsigned char*) calloc(pixelArraySize,sizeof(unsigned char));
	stepSize = windowWidth*3;
}

void framebuffer_t::setWindowWidth(int w)
{
	windowWidth = w;
}


void framebuffer_t::setWindowHeight(int h)
{
	windowHeight = h;
}

int framebuffer_t::getWindowWidth()
{
	return windowWidth;
}

int framebuffer_t::getWindowHeight()
{
	return windowHeight;
}

unsigned char* framebuffer_t::getPixelValueArray()
{
	return pixelValueArray;
}

color_t framebuffer_t::getPixelValue(int w, int h)
{
	int red_component = pixelValueArray[h*stepSize + w*3 + 0];
	int green_component = pixelValueArray[h*stepSize + w*3 + 1];
	int blue_component = pixelValueArray[h*stepSize + w*3 + 2];

	color_t color(red_component, green_component, blue_component);
	return color;
}

void framebuffer_t::setPixelValue(int w, int h, color_t value)
{
	pixelValueArray[h*stepSize + w*3 + 0] = value.getR();
	pixelValueArray[h*stepSize + w*3 + 1] = value.getG();
	pixelValueArray[h*stepSize + w*3 + 2] = value.getB();
}

void framebuffer_t::clearPixelValueArray()
{
	for ( int i = 0 ; i < pixelArraySize ; i++ )
		pixelValueArray[i] = 0;
}

