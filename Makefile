CC = g++
CFLAGS = -Wall
PROG = assign_2
SRCS = main.cpp 
LIBS = -lglut -lGL -lGLU -lm

all: $(PROG)

$(PROG): $(SRCS) clipping_3d_t.o color_t.o coordinates_3D_t.o drawing_3d_t.o framebuffer_t.o line_3d_t.o math_utility.o matrix_t.o pipeline_t.o rasterizer_t.o transformations.o vector_t.o 
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) clipping_3d_t.o color_t.o coordinates_3D_t.o drawing_3d_t.o framebuffer_t.o line_3d_t.o math_utility.o matrix_t.o pipeline_t.o rasterizer_t.o transformations.o vector_t.o  $(LIBS)

clipping_3d_t.o : clipping_3d_t.cpp
	$(CC) -c clipping_3d_t.cpp
	
color_t.o: color_t.cpp
	$(CC) -c color_t.cpp

coordinates_3D_t.o: coordinates_3D_t.cpp
	$(CC) -c coordinates_3D_t.cpp
	
drawing_3d_t.o: drawing_3d_t.cpp
	$(CC) -c drawing_3d_t.cpp

framebuffer_t.o: framebuffer_t.cpp
	$(CC) -c framebuffer_t.cpp

line_3d_t.o: line_3d_t.cpp
	$(CC) -c line_3d_t.cpp
	
math_utility.o: math_utility.cpp
	$(CC) -c math_utility.cpp
	
matrix_t.o: matrix_t.cpp
	$(CC) -c matrix_t.cpp
	
pipeline_t.o: pipeline_t.cpp
	$(CC) -c pipeline_t.cpp

rasterizer_t.o: rasterizer_t.cpp
	$(CC) -c rasterizer_t.cpp
	
transformations.o: transformations.cpp
	$(CC) -c transformations.cpp

vector_t.o: vector_t.cpp
	$(CC) -c vector_t.cpp

clean:
	rm -f $(PROG) *.o
