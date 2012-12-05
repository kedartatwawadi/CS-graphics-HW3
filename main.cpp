/*
 * main2.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: ayesha, kedar
 */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include "clipping_3d_t.h"
#include "color_t.h"
#include "coordinates_3D_t.h"
#include "drawing_3d_t.h"
#include "framebuffer_t.h"
#include "line_3d_t.h"
#include "math_utility.h"
#include "matrix_t.h"
#include "pipeline_t.h"
#include "rasterizer_t.h"
#include "transformations.h"
#include "vector_t.h"

int imageWidth,imageHeight, count=0;
unsigned char* image;
drawing_3d_t draw_wcs, draw_vcs, draw_ccs, draw_ndcs, draw_dcs, draw_ccs_clipped, draw_ndcs_clipped, draw_dcs_clipped, drawing_perspective;
framebuffer_t buffer;
rasterizer_t rasterizer;
pipeline_t orthographic_pipeline;

void scale_ccs_ndcs_vectors(vector_t &v1, vector_t &v2);
void setCameraParameters(drawing_3d_t &drawing, vector_t eye, vector_t lookat, vector_t up_vector
							, double L, double R, double T, double B, double N, double F);
void findCameraPositions(drawing_3d_t &drawing, int case_index);
void modify_camera(drawing_3d_t drawing1, drawing_3d_t &drawing2);
void modify_clipped_camera();
void setCameraPositions(drawing_3d_t drawing);


void startRasterizing(drawing_3d_t drawing) {
	rasterizer.setCanvas(drawing);
    rasterizer.setBuffer(buffer);
    rasterizer.rasterize();
    image = rasterizer.getBuffer().getPixelValueArray();
}

void makeImage(char* fileName) {
	drawing_3d_t drawing(fileName);
	imageWidth  = drawing.getWindowWidth();
	imageHeight = drawing.getWindowHeight();
	pipeline_t mypipeline(drawing, 0);
	buffer.setFrameBuffer(imageWidth, imageHeight);
	startRasterizing(drawing);
	setCameraPositions(drawing);
	drawing_perspective = drawing;
}

void init(void) {
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void display(void) {
   glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i(0, 0);
   glDrawPixels(imageWidth, imageHeight, GL_RGB, GL_UNSIGNED_BYTE, image);
   glFlush();
}

void reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho (0, w, 0, h, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

void startOrthographicPipeline(drawing_3d_t drawing) {
	  orthographic_pipeline.executePipeline(drawing,1);
	  startRasterizing(drawing);
}

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 27:
         exit(0);

      case '1':
    	  startOrthographicPipeline(draw_wcs);
    	  break;

      case '2':
    	  startOrthographicPipeline(draw_vcs);
    	  break;

      case '3':
    	  if (count==0) startOrthographicPipeline(draw_ccs);
    	  else startOrthographicPipeline(draw_ccs_clipped);
    	  break;

      case '4':
    	  if (count==0) startOrthographicPipeline(draw_ndcs);
    	  else startOrthographicPipeline(draw_ndcs_clipped);
    	  break;

      case '5':
    	  if (count==0) startOrthographicPipeline(draw_dcs);
    	  else startOrthographicPipeline(draw_dcs_clipped);
    	  break;

      case 'd':
    	  startRasterizing(drawing_perspective);
    	  break;

      case 'c':
      	  count = (count+1)%2;
      	  break;
   }
   glutPostRedisplay();
}
int main(int argc, char** argv)
{
   makeImage(argv[1]);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(imageWidth,imageHeight);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutIdleFunc(display);
   glutMainLoop();
   return 0;
}







/******************************************************************************************************/































/****************************************************************************************************/


void scale_ccs_ndcs_vectors(vector_t &v1, vector_t &v2){
	v1.setX(v1.getX()*100);
	v1.setY(v1.getY()*100);
	v1.setZ(v1.getZ()*100);
	v2.setX(v2.getX()*100);
	v2.setY(v2.getY()*100);
	v2.setZ(v2.getZ()*100);
}

void setCameraParameters(drawing_3d_t &drawing, vector_t eye, vector_t lookat, vector_t up_vector, double L, double R, double T, double B, double N, double F) {
	drawing.setE(eye);
	drawing.setA(lookat);
	drawing.setUp(up_vector);
	drawing.setL(L);
	drawing.setR(R);
	drawing.setT(T);
	drawing.setB(B);
	drawing.setN(N);
	drawing.setF(F);
}

void findCameraPositions(drawing_3d_t &drawing, int case_index) {
	vector_t v_min = drawing.getWcsMin();
	vector_t v_max = drawing.getWcsMax();
	double x_min = v_min.getX();
	double y_min = v_min.getY();
	double z_min = v_min.getZ();
	double x_max = v_max.getX();
	double y_max = v_max.getY();
	double z_max = v_max.getZ();

	double e_x, e_y, e_z, a_x, a_y, a_z, up_x, up_y, up_z, L, R, T, B, N, F;
	
	
	if (case_index == 4 || case_index == 7){
		//dcs, clipped dcs.
		e_x = (x_max + x_min)/2;
		e_y = (y_max + y_min)/2;
		e_z = 10;

		a_x = e_x; a_y = e_y; a_z = 0;
		up_x = 0; up_y = 1; up_z = 0;

		L = (x_min - x_max);
		R = (x_max - x_min);
		T = (y_max - y_min);
		B = (y_min - y_max);
		
		if(R > T) 
		{
		T = R ;
		B = -T;
		}
		else 
		{
		R = T;
		L = -R;
		} 
		
		N = 5;
		F = 15;
	}

	else {
		e_x = (x_max + x_min)/2;
		e_y = 2*y_max - y_min;
		e_z = (z_max + z_min)/2;

		a_x = e_x; a_y = (y_max + y_min)/2; a_z = e_z;
		up_x = 1; up_y = 0, up_z = 0;

		L = (z_min - z_max);
		R = (z_max - z_min);
		T = (x_max - x_min);
		B = (x_min - x_max);
		
		if(R > T) 
		{
		T = R ;
		B = -T;
		}
		else 
		{
		R = T;
		L = -R;
		} 
		
		N = (y_max-y_min)/2;
		F = N*5;
	}

	vector_t eye(e_x, e_y, e_z);
	vector_t lookat(a_x, a_y, a_z);
	vector_t up_vector(up_x, up_y, up_z);
	setCameraParameters(drawing, eye, lookat, up_vector, L, R, T, B, N, F);
}

drawing_3d_t setCamera(drawing_3d_t drawing, int case_index) {
	drawing_3d_t ortho_drawing;
	ortho_drawing.setWindowWidth(drawing.getWindowWidth());
	ortho_drawing.setWindowHeight(drawing.getWindowHeight());
	int number_of_lines = drawing.getNumberOfLines();
	ortho_drawing.setNumberOfLines(number_of_lines);
	line_3d_t* line_array = (line_3d_t*) calloc(number_of_lines,sizeof(line_3d_t));
	line_3d_t* drawing_line_array = (line_3d_t*) calloc(number_of_lines,sizeof(line_3d_t));
	drawing_line_array = drawing.getLineArray();
	coordinates_3D_t cood1,cood2;
	coordinates_3D_t line_cood1, line_cood2;
	vector_t v1, v2;
	for (int i = 0; i < number_of_lines; i++) {
		line_cood1 = drawing_line_array[i].getV0();
		line_cood2 = drawing_line_array[i].getV1();
		switch (case_index) {
			case 0: // wcs
				v1 = line_cood1.getWcs();
				v2 = line_cood2.getWcs();
				break;

			case 1: //vcs
				v1 = line_cood1.getVcs();
				v2 = line_cood2.getVcs();
				break;

			case 2: //ccs ------------------->
				v1 = line_cood1.getNdcs();
				v2 = line_cood2.getNdcs();
				scale_ccs_ndcs_vectors(v1,v2);
				break;

			case 3://ndcs
				v1 = line_cood1.getNdcs();
				v2 = line_cood2.getNdcs();
				scale_ccs_ndcs_vectors(v1,v2);
				break;

			case 4://dcs
				v1 = line_cood1.getDcs();
				v2 = line_cood2.getDcs();
				break;

			case 5://ccs clipped
				v1 = line_cood1.getNdcsClipped();
				v2 = line_cood2.getNdcsClipped();
				scale_ccs_ndcs_vectors(v1,v2);
				break;

			case 6://ndcs clipped
				v1 = line_cood1.getNdcsClipped();
				v2 = line_cood2.getNdcsClipped();
				scale_ccs_ndcs_vectors(v1,v2);
				break;

			case 7://dcs clipped//double e_x = 0;
				v1 = line_cood1.getDcsClipped();
				v2 = line_cood2.getDcsClipped();
				break;

			default:
				v1 = line_cood1.getDcsClipped();
				v2 = line_cood2.getDcsClipped();
				break;
		}
		cood1.setWcs(v1);
		cood2.setWcs(v2);
		line_array[i].setV0(cood1);
		line_array[i].setV1(cood2);
	}
	ortho_drawing.setLineArray(line_array);
	findCameraPositions(ortho_drawing, case_index);
	return ortho_drawing;
}

void modify_camera(drawing_3d_t drawing1, drawing_3d_t &drawing2){
	drawing2.setE(drawing1.getE());
	drawing2.setA(drawing1.getA());
	drawing2.setUp(drawing1.getUp());
	drawing2.setL(drawing1.getL());
	drawing2.setR(drawing1.getR());
	drawing2.setT(drawing1.getT());
	drawing2.setB(drawing1.getB());
	drawing2.setN(drawing1.getN());
	drawing2.setF(drawing1.getF());
}

void modify_clipped_camera() {
	modify_camera(draw_ccs, draw_ccs_clipped);
	modify_camera(draw_ndcs, draw_ndcs_clipped);
	modify_camera(draw_dcs, draw_dcs_clipped);
}

void setCameraPositions(drawing_3d_t drawing) {
	draw_wcs = setCamera(drawing,0);
	draw_vcs = setCamera(drawing,1);
	draw_ccs = setCamera(drawing,2);
	draw_ndcs = setCamera(drawing,3);
	draw_dcs = setCamera(drawing,4);
	draw_ccs_clipped = setCamera(drawing,5);
	draw_ndcs_clipped = setCamera(drawing,6);
	draw_dcs_clipped = setCamera(drawing,7);
	modify_clipped_camera();
}






/*!
 
 This is a simple implementation of the 3D graphics pipeline implemented by:<br>
 Ayesha Mudassir [09007014]<br>
 Kedar Tatwawadi [09D07022]<br>
 Under the guidance of Prof Parag Chaudhari , CSE IIT Bombay <br>
 The project was undertaken as a part of <b> CS675: Introduction to Computer Graphics</b> course.<br>
 \mainpage 3D Graphics Pipeline Implementation
  \section intro_sec Introduction
  This is a simple code for implementing a 3D Graphics pipeline .<br> 
  The graphics pipeline and the modelling-viewing pipeline are shown below :<br>
<div align="center">
  <b> The Graphics pipeline</b>
  <img src="images/pipeline.png" alt="Graphics Pipeline" width="400" align="middle"  />
  <br>  <b>The Modelling Viewing Pipeline</b>
  <img src="images/s0.png" alt="Graphics Pipeline" width="400" align="middle"  />
  <br>
  
</div>
  
   \section sec_8 Implementation Details
  
  Our aim was to demonstrate the working of 3D graphics pipeline.<br>
  For this, we displayed the appropriate orthographic camera views for each of wcs, vcs, ccs, ndcs and their clipped counterparts.
  The implementation specifications are as follows:<br>
  <ul>
  	<li>Define the camera center position (E), lookat point position, up vector
		in the WCS and distance to near and far clipping planes, L,R,T,B
		extents of the near clipping window in the VCS in the scene file. Also,
		define a viewport as explained in class. Note this viewport must fit
		inside your framebuffer.
	<li>Define a 3D object using lines in your scene file. (.scn) file.
	<li>You have to draw the view frustum with the near and far clipping
		planes, and the object with lines using your own rasterizer into your
		framebuffer object. Start in the WCS.
	<li>To visualize the frustum and camera center (E), you will need to setup
		a second orthographic camera. This you can do in code and need not
		read from the file, but you have to do this using your pipeline. Also,
		position the orhtographic camera at an appropriate distance and angle
		so that the frustum and object to be visualized is completely visible. So
		there are two instances of your pipeline that will exist - one visualizing
		the stages in the other.
	<li>Create a keyboard callback function and map the keys 1,2,3,4,5 to
		move from WCS to VCS to CCS to NDCS to DCS in the perspective
		pipeline. Whatever is the transformed frustum and object for this
		pipeline is drawn to the screen using the orthographic pipeline.
	<li>Add a key ’c’ that activates clipping while we are in the CCS. If clip-
		ping it activated in CCS, it will carry forward in NDCS and DCS.
	<li>It should also be possible to press the keys 1 to 5 in any order and
		jump to the appropriate stage in the pipeline.

  </ul>
  
  
  
  <p>
  
  The following classes were implemented:
  <ul>
  	<li> color_t       </li>
  	<li> drawing_3d_t     </li>
  	<li> rasterizer_t  </li>
  	<li> clipping_3d_t     </li>
  	<li> framebuffer_t    </li>
  	<li> drawing_3d_t     </li>
  	<li> line_3d_t        </li>
  	<li> coordinates_3D_t </li>
  	<li> vector_t  </li>
  	<li> matrix_t  </li>
  </ul>
  
  </p>
  \section sec_1 File Input Format
  The program expects a *.scn file format. The format is described given below:<br>
  <pre>
	<window_width> <window_height> 
	<e_x,e_y,e_z>
	<a_x,a_y,a_z>
	<up_x,up_y,up_z>
	<L,R,T,B,N,F>

	<number_of_lines>
	l <x0, y0, z0> <x1, y1, z1> 
	l <x2, y2, z2> <x3, y3, z3> 
	l <x4, y4, z4> <x5, y5, z5> 
	l <x6, y6, z6> <x7, y7, z7> 
	l <x8, y8, z8> <x9, y9, z9>
	 
  </pre>
  <br>
  
  \section sec_2 User Interface
  The user interface is as follows:<br>
  The clipping frustum is drawn in green.While, the figure is drawn in red.<br>
  The Keyboard interface is as follows:<br>
  <ul>
  	<li>1 : wcs </li>
  	<li>2 : vcs </li>
  	<li>3 : ccs </li>
  	<li>4 : ndcs </li>
  	<li>5 : dcs </li>
  	<li>c + 3 : ccs clipped </li>
  	<li>c + 4 : ndcs clipped </li>
  	<li>c + 5 : dcs clipped </li>
  	<li> d  : perspective camera view </li>
  </ul>
  
  
  
  \section sec_3 Orthographic Camera positioning 
  
 	For most of the cases , ( except dcs and dcs_clipped) the algorithm for finding a simpe camera position is as follows:
 	<ul>
 		<li> Find x_max, x_min, y_max, y_min, z_max, z_min. Where they represent the coordinates of the bounding box in the given coordinate system</li>
 		<li> Let (c_x, c_y,c_z) be the centre coordinates , then place the camera along the line parallel to y-axis through the centre. </li>
 		<li> The coordinates are:   <br>
 			e_x = (x_max + x_min)/2;<br>
			e_y = 2*y_max - y_min;  <br>
			e_z = (z_max + z_min)/2;<br>
		<li> The look at direction is towards the bounding box centre.<br>
			a_x = e_x; <br>
			a_y = (y_max + y_min)/2; <br>
		    a_z = e_z;<br>
		<li> The up direction is the x-axis <br>
			 up_x = 1; <br>
			 up_y = 0; <br>
			 up_z = 0; <br>
		<li> Set the L,R,T,B, N,F appropriately, so that the entire bounding box is present inside the orthographic frustum.
		</li>
		<li> For ccs, ndcs, we scale the coordinates by 100 (for viewing purpose only), as the range [-1, 1] poses some problems.
	</ul>
	
	The entire code snippet can be found at: 
	
  	<p>
  	<ul>
  	  <li>As for dcs, dcs_clipped, it makes sense to place the camera on the z-axis .</li>
  	  <li>We expect the orthographic view for dcs case to match the view of the perspective camera then! </li>
  	  <li> We proceed in a similar way as for other cases, just that, we place the camera on the z-axis , 
  	  with lookat point towards the centre </li>
  	  <li>  have a look at the function doxygen documentation for function findCameraPositions(); </li>  
  	</ul>
  
 	</p>
    \section sec_6 Examples
    
    The house2.scn file is as follows:<br>
    <pre>
    
400,400
-150,-150,250
-100,-100,200
0,0,1
-200,200,200,-200,200,500 

22
l 0,0,0 150,0,0
l 150,0,0 150,200,0
l 150,200,0 0,200,0
l 0,200,0 0,0,0
l 0,0,0 0,0,200
l 150,0,0 150,0,200
l 150,200,0 150,200,200
l 0,200,0 0,200,200
l 0,0,200 75,0,250
l 75,0,250 150,0,200
l 150,0,200 150,200,200
l 150,200,200 75,200,250
l 75,200,250 0,200,200
l 0,200,200 0,0,200
l 75,0,250 75,200,250
l 50,0,0 50,0,75
l 50,0,75 100,0,75
l 100,0,75 100,0,0
l 50,0,120 100,0,120
l 100,0,120 100,0,150
l 100,0,150 50,0,150
l 50,0,150 50,0,120
    
    </pre><br>
    
    The execution proceeds as follows:<br>
    <pre>
    make                            --- [ compiles the program using the Makefile]
    ./assign_2 images/house2.scn     --- [ Execute the assig_1 executable formed  ]
    </pre><br>
    
    The screenshots are as follows:<br>
    <div align="center">

	 <h3> Final perspective camera view [d]</h3>
     <img src="images/s1.png" alt="Graphics Pipeline" width="600" align="middle"  />
     <br><h3> Wcs View [1]</h3>
     <img src="images/s2.png" alt="Graphics Pipeline" width="600" align="middle"  />
     <br><h3> Vcs View [2]</h3>
     <img src="images/s3.png" alt="Graphics Pipeline" width="600" align="middle"  />
     <br><h3> Ccs View [3]</h3>
     <img src="images/s4.png" alt="Graphics Pipeline" width="600" align="middle"  />
     <br><h3> Ndcs View [4]</h3>
     <img src="images/s5.png" alt="Graphics Pipeline" width="600" align="middle"  />
     <br><h3> Dcs View [5]</h3>
     <img src="images/s6.png" alt="Graphics Pipeline" width="600" align="middle"  />
     <br><h3> Ccs Clipped [c + 3]</h3>
     <img src="images/s7.png" alt="Graphics Pipeline" width="600" align="middle"  />
     <br><h3> Ndcs Clipped [ c + 4]</h3>
     <img src="images/s8.png" alt="Graphics Pipeline" width="600" align="middle"  />
     <br><h3> Dcs Clipped view[c + 5]  </h3>
     <img src="images/s9.png" alt="Graphics Pipeline" width="600" align="middle"  />
     <br>
     
 </div> 
	


  \section refer References
  <ol>
  	 <li> <b>GLUT: </b> http://www.glprogramming.com/red/chapter08.html </li>
     <li> <b>FileReading:</b> http://www.cplusplus.com/reference/clibrary/cstring/strtok/ </li>
     <li> <b>FileReading:</b> http://www.cplusplus.com/reference/iostream/istream/getline/ </li>
     <li> <b>Color Values:</b> http://cloford.com/resources/colours/500col.htm </li>
     <li> <b>Clipper:</b> http://www.cse.iitb.ac.in/~paragc/teaching/2012/cs675/ [Clipping lecture notes] </li> 
     <li> <b>Line Rasterizer:</b>  http://www.cse.iitb.ac.in/~paragc/teaching/2012/cs675/demonotes.shtml#bresenham  </li> 
     <li> <b> All integer Bresenham:</b> http://homepage.smc.edu/kennedy_john/BRESENL.PDF </li>
     <li> <b>FloodFill:</b> http://en.wikipedia.org/wiki/Flood_fill </li> 
     <li> <b>ScanLine Fill: </b> http://lodev.org/cgtutor/floodfill.html </li> 
     <li> <b> 3D clipping:  </b> http://www.ugrad.cs.ubc.ca/~cs314/notes/clip3d.html 
  </ol> 
 
*/



