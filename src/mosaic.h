#ifndef MOSAIC_MATRIX_H
#define MOSAIC_MATRIX_H

struct mosaic_matrix {
	float *raw;
	unsigned int rows;
	unsigned int cols;
};

int mosaic_matrix_init(struct mosaic_matrix *matrix, unsigned int rows, unsigned int cols);
int mosaic_matrix_add(struct mosaic_matrix *m1, 
		struct mosaic_matrix *m2, 
		struct mosaic_matrix *result);
int mosaic_matrix_apply(struct mosaic_matrix *matrix, float (*func)(float));
int mosaic_matrix_multiply(struct mosaic_matrix *m1,
		struct mosaic_matrix *m2,
		struct mosaic_matrix *result);
int mosaic_matrix_assign(struct mosaic_matrix *matrix, float *values);
int mosaic_free(struct mosaic_matrix *matrix);
int mosaic_print(struct mosaic_matrix *matrix);
#endif
