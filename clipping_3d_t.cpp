/*
 * clipping_3d_t.cpp
 *
 *  Created on: Sep 24, 2012
 *      Author: ayesha, kedar
 */

#include "clipping_3d_t.h"
#include "vector_t.h"
#include "pipeline_t.h"
#include "matrix_t.h"
#include "transformations.h"
#include <stdlib.h>

clipping_3d_t::clipping_3d_t() {
	// TODO Auto-generated constructor stub
}

void clipping_3d_t::clip_line(line_3d_t &line) {
	int trivial_flag = 0;
	coordinates_3D_t cood1 = line.getV0();
	coordinates_3D_t cood2 = line.getV1();
	vector_t v_0 = cood1.getCcs();
	vector_t v_1 = cood2.getCcs();
	vector_t v_0_wcs = cood1.getWcs();
	vector_t v_1_wcs = cood2.getWcs();
	vector_t v_0_vcs = cood1.getVcs();
	vector_t v_1_vcs = cood2.getVcs();
	double w0 = cood1.getWCcs();
	double w1 = cood2.getWCcs();

	char OC0 = setOutcodes(v_0,w0);
	char OC1 = setOutcodes(v_1,w1);
	
	while(trivial_flag!=1)	{
		if ((OC0|OC1) == 0) {//trivially accept
			cood1.setCcsClipped(v_0);
			cood2.setCcsClipped(v_1);
			line.setClipFlag(0);
			trivial_flag = 1;
			vector_t v_ndcs_clipped1 = generateNdcsClipped(v_0,w0);
			vector_t v_ndcs_clipped2 = generateNdcsClipped(v_1,w1);
			cood1.setNdcsClipped(v_ndcs_clipped1);
			cood2.setNdcsClipped(v_ndcs_clipped2);
		}

		else if ((OC0 & OC1) != 0) {//trivially reject
			line.setClipFlag(1);
			trivial_flag = 1;
		}

		else if(OC0!=0) {
     		recomputeVertex(v_0,v_1,w0,w1,OC0);
			OC0 = setOutcodes(v_0,w0);
		}

		else if(OC1!=0) {
			recomputeVertex(v_1,v_0,w1,w0,OC1);
			OC1 = setOutcodes(v_1,w1);
		}
	}
	line.setV0(cood1);
	line.setV1(cood2);
}



void clipping_3d_t::clip_line_orthographic(line_3d_t &line){
	int trivial_flag = 0;
	coordinates_3D_t cood1 = line.getV0();
	coordinates_3D_t cood2 = line.getV1();
	vector_t v_0 = cood1.getNdcs();
	vector_t v_1 = cood2.getNdcs();
	double w0 = 1;
	double w1 = 1;

	char OC0 = setOutcodes(v_0,w0);
	char OC1 = setOutcodes(v_1,w1);

	while(trivial_flag!=1)	{
		if ((OC0|OC1) == 0) {//trivially accept
			cood1.setNdcsClipped(v_0);
			cood2.setNdcsClipped(v_1);
			line.setClipFlag(0);
			trivial_flag = 1;
		}

		else if ((OC0 & OC1) != 0) {//trivially reject
			line.setClipFlag(1);
			trivial_flag = 1;
		}

		else if(OC0!=0) {
			recomputeVertex(v_0,v_1,w0,w1,OC0);
			OC0 = setOutcodes(v_0,w0);
		}

		else if(OC1!=0) {
			recomputeVertex(v_1,v_0,w1,w0,OC1);
			OC1 = setOutcodes(v_1,w1);
		}
	}
	line.setV0(cood1);
	line.setV1(cood2);

}

void clipping_3d_t::recomputeVertex(vector_t &v0, vector_t v1,double w0, double w1,char OC) {
	double x0 = v0.getX();
	double y0 = v0.getY();
	double z0 = v0.getZ();
	double x1 = v1.getX()*w0/w1;
	double y1 = v1.getY()*w0/w1;
	double z1 = v1.getZ()*w0/w1;

	//if (w0>0){
		if((OC&1)!=0) {// x0 < -w
			y0 = (y1-y0)/(x1-x0)*(-w0-x0) + y0;
			z0 = (z1-z0)/(x1-x0)*(-w0-x0) + z0;
			x0 = -w0;
		}
		else if((OC&2)!=0) {// x0 > w
			y0 = (y1-y0)/(x1-x0)*(w0-x0) + y0;
			z0 = (z1-z0)/(x1-x0)*(w0-x0) + z0;
			x0 = w0;
		}
		else if((OC&4)!=0) {// y0 < -w
			x0 = (x1-x0)/(y1-y0)*(-w0-y0) + x0;
			z0 = (z1-z0)/(y1-y0)*(-w0-y0) + z0;
			y0 = -w0;
		}
		else if((OC&8)!=0) {//y0>w
			x0 = (x1-x0)/(y1-y0)*(w0-y0) + x0;
			z0 = (z1-z0)/(y1-y0)*(w0-y0) + z0;
			y0 = w0;
		}
		else if((OC&16)!=0) {// z0 < -w
			x0 = (x1-x0)/(z1-z0)*(-w0-z0) + x0;
			y0 = (y1-y0)/(z1-z0)*(-w0-z0) + y0;
			z0 = -w0;
		}
		else if((OC&32)!=0) {//z0>w
			x0 = (x1-x0)/(z1-z0)*(w0-z0) + x0;
			y0 = (y1-y0)/(z1-z0)*(w0-z0) + y0;
			z0 = w0;
		}
	//}


	v0.setX(x0);
	v0.setY(y0);
	v0.setZ(z0);
	
}

char setOutcodes(vector_t v, double w) {
	char OC = 0;
	int sign_flag;
	if (w > 0) sign_flag = 0;
	else sign_flag = 1;

	double x = v.getX();
	double y = v.getY();
	double z = v.getZ();

	if (sign_flag == 0) {
		if (x<-w) OC += 1;
		if (x>w) OC += 2;
		if (y<-w) OC += 4;
		if (y>w) OC += 8;
		if (z<-w) OC += 16;
		if (z>w) OC += 32;
	}

	else {
		if (x>-w) OC += 1;
		if (x<w) OC += 2;
		if (y>-w) OC += 4;
		if (y<w) OC += 8;
		if (z>-w) OC += 16;
		if (z<w) OC += 32;
	}
	return OC;
}

void clipping_3d_t::clip_drawing(drawing_3d_t &drawing, int camera_flag) {
	setNumOfLines(drawing.getNumberOfLines());
	setLineArray(drawing.getLineArray());
	line_3d_t line;
	for (int i = 0; i < NumOfLines; i++) {
		line = lineArray[i];
		if (camera_flag == 0) clip_line(line);
		else if (camera_flag == 1) clip_line_orthographic(line);
		lineArray[i] = line;
		
	}
}

vector_t generateNdcsClipped(vector_t ccs_clipped, double w_ccs) {
	double x = ccs_clipped.getX()/w_ccs;
	double y = ccs_clipped.getY()/w_ccs;
	double z = ccs_clipped.getZ()/w_ccs;
	vector_t vector1(x,y,z);
	return vector1;
}

line_3d_t* clipping_3d_t::getLineArray() {
	return lineArray;
}

void clipping_3d_t::setLineArray(line_3d_t* line_array) {
	lineArray = line_array;
}

int clipping_3d_t::getNumOfLines(){
	return NumOfLines;
}

void clipping_3d_t::setNumOfLines(int num_of_lines) {
	NumOfLines = num_of_lines;
}
