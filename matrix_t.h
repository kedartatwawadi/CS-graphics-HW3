/*
 * matrix_t.h
 *
 *  Created on: Sep 22, 2012
 *      Author: ayesha, kedar
 */

#ifndef MATRIX_T_H_
#define MATRIX_T_H_

class matrix_t {
public:
	matrix_t();
	matrix_t(int num_of_rows, int num_of_columns);
	matrix_t(int rum_of_rows, int num_of_columns, double* matrix_array);

	double getElement(int row_number, int column_number);
	void setElement(double entry, int row_number, int column_number);

	int getNumColumns();
	void setNumColumns(int num_of_columns);

	int getNumRows();
	void setNumRows(int num_of_rows);

	double* getElementArray();
	void setElementArray(double* element_array);

private:
	int numRows;
	int numColumns;
	double* element;

};

#endif /* MATRIX_T_H_ */
