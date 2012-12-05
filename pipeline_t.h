/*
 * pipeline_t.h
 *
 *  Created on: Sep 17, 2012
 *      Author: ayesha, kedar
 */

#ifndef PIPELINE_T_H_
#define PIPELINE_T_H_
#include "vector_t.h"
#include "coordinates_3D_t.h"
#include "drawing_3d_t.h"
#include "matrix_t.h"

class pipeline_t {
public:
	pipeline_t();
	pipeline_t(drawing_3d_t &drawing,int camera_flag);
	void executePipeline(drawing_3d_t &drawing,int camera_flag);
	void processCoordinateUnClipped(coordinates_3D_t &cood,matrix_t wcs_to_vcs,matrix_t vcs_to_ccs);
	void processOrthographicCoordinate(coordinates_3D_t &cood,matrix_t wcs_to_vcs,matrix_t vcs_ndcs_ortho);
	void clipLine(line_3d_t &line);

	line_3d_t* getLineArray();
	void setLineArray(line_3d_t* line_array) ;
	void clipDrawing();
	int getNumOfLines();
	void setNumOfLines(int num_of_lines);

	void setViewPort(double Lw, double Rw, double Tw, double Bw);

private:
	int NumOfLines;
	line_3d_t* lineArray;
};

#endif /* PIPELINE_T_H_ */
