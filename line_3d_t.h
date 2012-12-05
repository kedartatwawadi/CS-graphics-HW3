/*
 * line_3d_t.h
 *
 *  Created on: Sep 24, 2012
 *      Author: ayesha, kedar
 */

#ifndef LINE_3D_T_H_
#define LINE_3D_T_H_

#include "coordinates_3D_t.h"

class line_3d_t {
public:
	line_3d_t();
	line_3d_t(coordinates_3D_t v_0, coordinates_3D_t v_1);

	int getClipFlag();
	void setClipFlag(int flag);

	coordinates_3D_t getV0();
	void setV0(coordinates_3D_t v_0);

	coordinates_3D_t getV1() ;
	void setV1(coordinates_3D_t v_1);

private:
	coordinates_3D_t v0;
	coordinates_3D_t v1;
	int clipFlag;
};

#endif /* LINE_3D_T_H_ */
