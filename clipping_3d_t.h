/*
 * clipping_3d_t.h
 *
 *  Created on: Sep 24, 2012
 *      Author: ayesha, kedar
 */

#include "pipeline_t.h"
#include "vector_t.h"

#ifndef CLIPPING_3D_T_H_
#define CLIPPING_3D_T_H_

class clipping_3d_t {
public:
	clipping_3d_t();
	void clip_line(line_3d_t &line);
	void clip_line_orthographic(line_3d_t &line);
	void recomputeVertex(vector_t &v0, vector_t v1,double w0,double w1,char OC);
	void clip_drawing(drawing_3d_t &drawing, int camera_flag);

	line_3d_t* getLineArray();
	void setLineArray(line_3d_t* line_array);

	int getNumOfLines();
	void setNumOfLines(int num_of_lines);

private:
	int NumOfLines;
	line_3d_t* lineArray;
};

char setOutcodes(vector_t v, double w);
vector_t generateNdcsClipped(vector_t ccs_clipped, double w_ccs);
#endif /* CLIPPING_3D_T_H_ */
