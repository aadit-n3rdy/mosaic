#include "mosaic.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static inline float mosaic_matrix_get(struct mosaic_matrix mat, unsigned int r, unsigned int c) {
	return (mat.raw[r*mat.cols + c]);
}

int mosaic_matrix_init(struct mosaic_matrix *matrix, float *values,
		unsigned int rows, unsigned int cols) {
	matrix->raw = values;
	matrix->rows = rows;
	matrix->cols = cols;
	return 0;
}
int mosaic_matrix_add(struct mosaic_matrix m1, 
		struct mosaic_matrix m2, 
		struct mosaic_matrix *result) {
	unsigned int rows = m1.rows;
	unsigned int cols = m1.cols;
	unsigned int i = 0;
	unsigned int j = 0;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			result->raw[i*cols + j] = m1.raw[i*cols + j] + m2.raw[i*cols + j];
		}
	}
	return 0;
}
int mosaic_matrix_apply(struct mosaic_matrix matrix, float (*func)(float)) {
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int rows = matrix.rows;
	unsigned int cols = matrix.cols;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			matrix.raw[i*cols + j] = (*func)(matrix.raw[i*cols + j]);
		}
	}
	return 0;
}

int mosaic_matrix_multiply(struct mosaic_matrix m1, 
		struct mosaic_matrix m2, 
		struct mosaic_matrix *result) {
	unsigned int m1_rows = m1.rows;
	unsigned int m1_cols = m1.cols;
	unsigned int m2_cols = m2.cols;
	unsigned int r = 0;
	unsigned int c = 0;
	unsigned int i = 0;

	result->rows = m1_rows;
	result->cols = m2_cols;

	if (m1_cols != m2.rows) {
		return -1;
	}

	for (r = 0; r < m1_rows; r++) {
		for (c = 0; c < m2_cols; c++) {
			float sum = 0;
			for (i = 0; i < m1_cols; i++) {
				sum += m1.raw[r*m1_cols + i] * m2.raw[i*m2_cols + c];
			}
			result->raw[r*m2_cols + c] = sum;
		}
	}
	return 0;
}



int mosaic_print(struct mosaic_matrix matrix) {
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int rows = matrix.rows;
	unsigned int cols = matrix.cols;
	for (i = 0; i < rows; i++) {
		printf("[");
		for (j = 0; j < cols; j++) {
			printf(" %30.3f ", matrix.raw[cols*i + j]);
		}
		printf("]\n");
	}
	return 0;
}

int mosaic_copy(struct mosaic_matrix from, struct mosaic_matrix *to) {
	to->rows = from.rows;
	to->cols = from.cols;
	memcpy(from.raw, to->raw, from.rows * from.cols * sizeof(float));
	return 0;
}

int mosaic_elem_row_sum(struct mosaic_matrix mat, unsigned int result,
		unsigned int op,
		float coeff) {
	printf("row_sum r%u is r%u + r%u * %f\n", result, result, op, coeff);
	unsigned int cols = mat.cols;
	unsigned int res_offset = result * cols;
	unsigned int op_offset = op * cols;
	for (unsigned int i = 0; i < cols; i++) {
		mat.raw[res_offset+i] = mat.raw[res_offset+i] + (mat.raw[op_offset+i] * coeff);
	}
	return 0;
}

int mosaic_elem_row_swap(struct mosaic_matrix mat, unsigned int r1, unsigned int r2) {
	printf("swapping %u %u \n", r1, r2);
	unsigned int r1_offset = r1 * mat.cols;
	unsigned int r2_offset = r2 * mat.cols;
	float tmp;
	for (unsigned int i = 0; i < mat.cols; i++, r1_offset++, r2_offset++) {
		tmp = mat.raw[r1_offset];
		mat.raw[r1_offset] = mat.raw[r2_offset];
		mat.raw[r2_offset] = tmp;
	}
	return 0;
}

int mosaic_lower_tri(struct mosaic_matrix *mat) {
	return 0;
}

int mosaic_upper_tri(struct mosaic_matrix mat) {
	unsigned int c = 0;
	unsigned int i = 0;
	unsigned int swaps = 0;
	for (c = 0; c < mat->cols-1; c++) {
		if (mat->raw[c + c*mat->cols] == 0) {
			for (i = c+1; i < mat->rows; i++) {
				if (mosaic_matrix_get(mat, i, c) != 0) {
					mosaic_elem_row_swap(mat, c, i);
					swaps++;
					break;
				}
			}
			if (i == mat->rows) {
				continue;
			}
		}
		for (i = c+1; i < mat->rows; i++) {
			mosaic_elem_row_sum(mat, i, c, 
					-mosaic_matrix_get(mat, i, c)/mosaic_matrix_get(mat, c, c));

		}
	}
	return swaps;
}

float mosaic_determinant(struct mosaic_matrix *mat) {
	float *diag_raw = malloc(mat->rows * mat->cols * sizeof(float));
	float det = 1;
	struct mosaic_matrix diag;
	memcpy(diag_raw, mat->raw, mat->rows * mat->cols * sizeof(float));
	diag.raw = diag_raw;
	diag.rows = mat->rows;
	diag.cols = mat->cols;
	mosaic_upper_tri(&diag);
	for (unsigned int i = 0; i < diag.rows; i++) {
		det = det * mosaic_matrix_get(&diag, i, i);
		if (det == 0) {
			break;
		}
	}
	free(diag_raw);
	return det;
}
