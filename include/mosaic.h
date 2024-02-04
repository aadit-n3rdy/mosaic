#ifndef MOSAIC_MATRIX_H
#define MOSAIC_MATRIX_H

struct mosaic_matrix {
	float *raw;
	unsigned int rows;
	unsigned int cols;
};

int mosaic_matrix_init(struct mosaic_matrix* matrix, float *values, 
		unsigned int rows, unsigned int cols);

int mosaic_matrix_add(struct mosaic_matrix m1, 
		struct mosaic_matrix m2, 
		struct mosaic_matrix* result);

int mosaic_matrix_apply(struct mosaic_matrix matrix, float (*func)(float));

int mosaic_matrix_multiply(struct mosaic_matrix m1,
		struct mosaic_matrix m2,
		struct mosaic_matrix* result);

int mosaic_print(struct mosaic_matrix* matrix);

int mosaic_copy(struct mosaic_matrix from, struct mosaic_matrix* to);

int mosaic_elem_row_swap(struct mosaic_matrix mat, unsigned int r1, unsigned int r2);

int mosaic_elem_row_sum(struct mosaic_matrix mat, unsigned int result, unsigned int op, float coeff);

int mosaic_upper_tri(struct mosaic_matrix mat);

float mosaic_determinant(struct mosaic_matrix mat);
#endif
