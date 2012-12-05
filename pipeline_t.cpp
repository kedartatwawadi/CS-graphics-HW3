/*
 * pipeline_t.cpp
 *
 *  Created on: Sep 17, 2012
 *      Author: ayesha, kedar
 */

#include "pipeline_t.h"
#include "math_utility.h"
#include "matrix_t.h"
#include "transformations.h"
#include "clipping_3d_t.h"
#include <stdlib.h>

pipeline_t::pipeline_t() {
	// TODO Auto-generated constructor stub
}

pipeline_t::pipeline_t(drawing_3d_t &drawing, int camera_flag) {

	setNumOfLines(drawing.getNumberOfLines());
	setLineArray(drawing.getLineArray());

	vector_t E = drawing.getE();
	vector_t A = drawing.getA();
	vector_t up = drawing.getUp();
	double L = drawing.getL();
	double R = drawing.getR();
	double T = drawing.getT();
	double B = drawing.getB();
	double N = drawing.getN();
	double F = drawing.getF();

	
	

	matrix_t wcs_to_vcs = WCS2VCS(E,A,up);
	if(camera_flag == 0){ //perspective camera
		matrix_t vcs_to_ccs = VCS2CCS(L,R,T,B,N,F);

		coordinates_3D_t cood1,cood2;
		line_3d_t line;
		for(int line_index = 0 ; line_index < NumOfLines ; line_index++){
			line = lineArray[line_index];
			cood1 = line.getV0();
			cood2 = line.getV1();
			processCoordinateUnClipped(cood1, wcs_to_vcs, vcs_to_ccs);
			processCoordinateUnClipped(cood2, wcs_to_vcs, vcs_to_ccs);
			line.setV0(cood1);
			line.setV1(cood2);
			lineArray[line_index] = line;

		}
	}

	else if(camera_flag == 1){//ortho
		matrix_t vcs_ndcs_ortho = VCS2NDCSOrtho(L,R,T,B,N,F);
		coordinates_3D_t cood1,cood2;
		line_3d_t line;
		for(int line_index = 0 ; line_index < NumOfLines ; line_index++){
			line = lineArray[line_index];
			cood1 = line.getV0();
			cood2 = line.getV1();
			processOrthographicCoordinate(cood1, wcs_to_vcs, vcs_ndcs_ortho);
			processOrthographicCoordinate(cood2, wcs_to_vcs, vcs_ndcs_ortho);
			line.setV0(cood1);
			line.setV1(cood2);
			lineArray[line_index] = line;
		}
	}
	
	clipping_3d_t clip_pipeline;
	clip_pipeline.clip_drawing(drawing, camera_flag);
	double Lw = 0;
	double Rw = (double) drawing.getWindowWidth();
	double Tw = (double) drawing.getWindowHeight();
	double Bw = 0;
	setViewPort(Lw, Rw, Tw, Bw);
}


void pipeline_t::executePipeline(drawing_3d_t &drawing,int camera_flag){
	setNumOfLines(drawing.getNumberOfLines());

	setLineArray(drawing.getLineArray());

	vector_t E = drawing.getE();
	vector_t A = drawing.getA();
	vector_t up = drawing.getUp();
	double L = drawing.getL();
	double R = drawing.getR();
	double T = drawing.getT();
	double B = drawing.getB();
	double N = drawing.getN();
	double F = drawing.getF();

	matrix_t wcs_to_vcs = WCS2VCS(E,A,up);

	if(camera_flag == 0){ //perspective camera
		matrix_t vcs_to_ccs = VCS2CCS(L,R,T,B,N,F);

		coordinates_3D_t cood1,cood2;
		line_3d_t line;
		for(int line_index = 0 ; line_index < NumOfLines ; line_index++){
			line = lineArray[line_index];
			cood1 = line.getV0();
			cood2 = line.getV1();
			processCoordinateUnClipped(cood1, wcs_to_vcs, vcs_to_ccs);
			processCoordinateUnClipped(cood2, wcs_to_vcs, vcs_to_ccs);
			line.setV0(cood1);
			line.setV1(cood2);
			lineArray[line_index] = line;
		}
	}

	else if(camera_flag == 1){//ortho
		matrix_t vcs_ndcs_ortho = VCS2NDCSOrtho(L,R,T,B,N,F);
		coordinates_3D_t cood1,cood2;
		line_3d_t line;
		for(int line_index = 0 ; line_index < NumOfLines ; line_index++){
			line = lineArray[line_index];
			cood1 = line.getV0();
			cood2 = line.getV1();
			processOrthographicCoordinate(cood1, wcs_to_vcs, vcs_ndcs_ortho);
			processOrthographicCoordinate(cood2, wcs_to_vcs, vcs_ndcs_ortho);
			line.setV0(cood1);
			line.setV1(cood2);

			vector_t v_0_wcs = cood1.getWcs();
			vector_t v_1_wcs = cood2.getWcs();
			vector_t v_0_vcs = cood1.getVcs();
			vector_t v_1_vcs = cood2.getVcs();
			lineArray[line_index] = line;
		}
	}

	clipping_3d_t clip_pipeline;
	clip_pipeline.clip_drawing(drawing, camera_flag);
	double Lw = 0;
	double Rw = (double) drawing.getWindowWidth();
	double Tw = (double) drawing.getWindowHeight();
	double Bw = 0;
	setViewPort(Lw, Rw, Tw, Bw);
}

void pipeline_t::processCoordinateUnClipped(coordinates_3D_t &cood, matrix_t wcs_to_vcs,matrix_t vcs_to_ccs ){


	vector_t vector_wcs = cood.getWcs();
	matrix_t vector_wcs_homo = generateHomogeneousCoodMatrix(vector_wcs); //generate the homogeneous coods of the point in wcs
	matrix_t vector_vcs_homo = matrixMultiply(wcs_to_vcs, vector_wcs_homo); //multiply the wcs to vcs transformation matrix with the homogeneous coods
	vector_t vector_vcs = generateVector(vector_vcs_homo); //get back the coods of the point from its homogeneous coods
	cood.setVcs(vector_vcs);//set vcs
	matrix_t vector_ccs_homo = matrixMultiply(vcs_to_ccs, vector_vcs_homo); //multiply the vcs to ccs transformation matrix with the homogeneous coods
	vector_t vector_ccs;
	vector_ccs.setX(vector_ccs_homo.getElement(0,0));
	vector_ccs.setY(vector_ccs_homo.getElement(1,0));
	vector_ccs.setZ(vector_ccs_homo.getElement(2,0));
	cood.setCcs(vector_ccs); //set ccs
	cood.setWCcs(vector_ccs_homo.getElement(3,0));
	vector_t vector_ndcs = generateVector(vector_ccs_homo);
	cood.setNdcs(vector_ndcs); //set ndcs

}


void pipeline_t::processOrthographicCoordinate(coordinates_3D_t &cood,matrix_t wcs_to_vcs,matrix_t vcs_ndcs_ortho){
	vector_t vector_wcs = cood.getWcs();
	matrix_t vector_wcs_homo = generateHomogeneousCoodMatrix(vector_wcs); //generate the homogeneous coods of the point in wcs
	matrix_t vector_vcs_homo = matrixMultiply(wcs_to_vcs, vector_wcs_homo); //multiply the wcs to vcs transformation matrix with the homogeneous coods
	vector_t vector_vcs = generateVector(vector_vcs_homo); //get back the coods of the point from its homogeneous coods
	cood.setVcs(vector_vcs);//set vcs
	matrix_t vector_ndcs_homo = matrixMultiply(vcs_ndcs_ortho, vector_vcs_homo);
	vector_t vector_ndcs = generateVector(vector_ndcs_homo);
	cood.setNdcs(vector_ndcs);
}





void pipeline_t::setViewPort(double Lw, double Rw, double Tw, double Bw) {
	int num_of_lines = NumOfLines;
	coordinates_3D_t cood1, cood2;
	vector_t vector1, vector2;
	for (int i = 0; i < num_of_lines; i++) {
		cood1 = lineArray[i].getV0();
		cood2 = lineArray[i].getV1();

		vector1 = cood1.getNdcs();
		vector1 = NDCS2DCS(vector1, Lw, Rw, Tw, Bw);
		vector2 = cood1.getNdcsClipped();
		vector2 = NDCS2DCS(vector2, Lw, Rw, Tw, Bw);
		cood1.setDcs(vector1);
		cood1.setDcsClipped(vector2);
		vector1 = cood2.getNdcs();
		vector1 = NDCS2DCS(vector1, Lw, Rw, Tw, Bw);
		vector2 = cood2.getNdcsClipped();
		vector2 = NDCS2DCS(vector2, Lw, Rw, Tw, Bw);
		cood2.setDcs(vector1);
		cood2.setDcsClipped(vector2);
		lineArray[i].setV0(cood1);
		lineArray[i].setV1(cood2);
	}
}

line_3d_t* pipeline_t::getLineArray() {
	return lineArray;
}

void pipeline_t::setLineArray(line_3d_t* line_array) {
	lineArray = line_array;
}

int pipeline_t::getNumOfLines() {
	return NumOfLines;
}

void pipeline_t::setNumOfLines(int num_of_lines) {
	NumOfLines = num_of_lines;
}

