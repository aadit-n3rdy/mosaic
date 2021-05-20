#include "mosaic.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int mosaic_matrix_init(struct mosaic_matrix *matrix, unsigned int rows, unsigned int cols) {
	matrix->raw = calloc(rows*cols, sizeof(float));
	matrix->rows = rows;
	matrix->cols = cols;
	return 0;
}
int mosaic_matrix_add(struct mosaic_matrix *m1, 
		struct mosaic_matrix *m2, 
		struct mosaic_matrix *result) {
	unsigned int rows = m1->rows;
	unsigned int cols = m1->cols;
	unsigned int i = 0;
	unsigned int j = 0;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			result->raw[i*cols + j] = m1->raw[i*cols + j] + m2->raw[i*cols + j];
		}
	}
	return 0;
}
int mosaic_matrix_apply(struct mosaic_matrix *matrix, float (*func)(float)) {
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int rows = matrix->rows;
	unsigned int cols = matrix->cols;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			matrix->raw[i*cols + j] = (*func)(matrix->raw[i*cols + j]);
		}
	}
	return 0;
}
int mosaic_matrix_multiply(struct mosaic_matrix *m1, 
		struct mosaic_matrix *m2, 
		struct mosaic_matrix *result) {
	unsigned int m1_rows = m1->rows;
	unsigned int m1_cols = m1->cols;
	unsigned int m2_cols = m2->cols;
	unsigned int r = 0;
	unsigned int c = 0;
	unsigned int i = 0;
	for (r = 0; r < m1_rows; r++) {
		for (c = 0; c < m2_cols; c++) {
			float sum = 0;
			for (i = 0; i < m1_cols; i++) {
				sum += m1->raw[r*m1_cols + i] * m2->raw[i*m2_cols + c];
			}
			result->raw[r*m2_cols + c] = sum;
		}
	}
	return 0;
}
int mosaic_matrix_assign(struct mosaic_matrix *matrix, float *values) {
	unsigned int i = 0;
	unsigned int count = matrix->rows * matrix->cols;
	while (i < count) {
		matrix->raw[i] = values[i];
		i++;
	}
	return 0;
}
int mosaic_free(struct mosaic_matrix *matrix) {
	free(matrix->raw);
	matrix->rows=0;
	matrix->cols=0;
	return 0;
}

int mosaic_print(struct mosaic_matrix *matrix) {
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int rows = matrix->rows;
	unsigned int cols = matrix->cols;
	for (i = 0; i < rows; i++) {
		printf("[");
		for (j = 0; j < cols; j++) {
			printf(" %30.3f ", matrix->raw[cols*i + j]);
		}
		printf("]\n");
	}
	return 0;
}

int mosaic_cpy(struct mosaic_matrix *from, struct mosaic_matrix *to) {
	mosaic_matrix_init(to, from->rows, from->cols);
	memcpy(from->raw, to->raw, from->rows * from->cols * sizeof(float));
	return 0;
}

