/*  
(a) Has a private pointer to a common framebuffer store object
as a data member, have methods to set and get this pointer. <br>
(b) Implemented in a draw line method an all integer version of
Bresenham line drawing that works in any octant.<br>
(c) A put pixel method that can turn on/off a pixel in the frame-
buffer store at position (x,y) by calling methods from the frame-
buffer store class.
*/

/*!
 * framebuffer_t.h
 *
 *  Created on: Aug 7, 2012
 *      Author: ayesha, kedar
 */

#ifndef FRAMEBUFFER_T_H_
#define FRAMEBUFFER_T_H_
#include "color_t.h"

class framebuffer_t {
public:
	// framebuffer_t  default constructor
	framebuffer_t();
		
	// framebuffer_t  constructor - Constructs a rgb framebuffer of the given width and height
	framebuffer_t(int w, int h);
	
	
	// sets the window width 
	void setWindowWidth(int w);
	// sets the window Height 
	void setWindowHeight(int h);
	
	
	// returns the width of the framebuffer
	int getWindowWidth();
	// returns the window Height
	int getWindowHeight();

	
	// returns a pointer to the framebuffer
	unsigned char* getPixelValueArray();
    
    
    //! sets the value of a pixel - parameter value is the value to which the pixel must be set
	void setPixelValue(int w, int h, color_t value);
	// returns the rgb components of the pixel(w,h)
	color_t getPixelValue(int w, int h);
        
    
    //clears the framebuffer
	void clearPixelValueArray();
	void setFrameBuffer(int w, int h);

private:
	int windowWidth;    /// the width of the frame buffer
	int windowHeight;   /// the heightt of the frame buffer
	int pixelArraySize; /// the size of the framebuffer for a RGB channel
	int stepSize;       /// the step size.
	unsigned char* pixelValueArray; /// pointer to the uchar array of pixel values.
};

#endif /* FRAMEBUFFER_T_H_ */
