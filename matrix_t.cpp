/*
 * matrix_t.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: ayesha, kedar
 */

#include "matrix_t.h"
#include <stdlib.h>

matrix_t::matrix_t() {
	// TODO Auto-generated constructor stub
}

matrix_t::matrix_t(int num_of_rows, int num_of_columns) {
	numRows = num_of_rows;
	numColumns = num_of_columns;
	element = (double*) calloc(num_of_rows*num_of_columns, sizeof(double));
}

matrix_t::matrix_t(int num_of_rows, int num_of_columns, double* matrix_array) {
	numRows = num_of_rows;
	numColumns = num_of_columns;
	element = (double*) calloc(num_of_rows*num_of_columns, sizeof(double));
	for(int i = 0 ; i < num_of_rows*num_of_columns ; i++){
		element[i] = matrix_array[i];
	}
}

double matrix_t::getElement(int row_number, int column_number) {
	return element[row_number*numColumns + column_number];
}

void matrix_t::setElement(double entry, int row_number, int column_number) {
	element[row_number*numColumns + column_number] = entry;
}

int matrix_t::getNumColumns() {
	return numColumns;
}

void matrix_t::setNumColumns(int num_of_columns) {
	numColumns = num_of_columns;
}

int matrix_t::getNumRows() {
	return numRows;
}

void matrix_t::setNumRows(int num_of_rows) {
	numRows = num_of_rows;
}

double* matrix_t::getElementArray(){
	return element;
}

void matrix_t::setElementArray(double* element_array){
	element = element_array;
}
