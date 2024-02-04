#include <mosaic.h>
#include <stdio.h>
#include <string.h>

int main() {
	struct mosaic_matrix m1;
	struct mosaic_matrix m2;
	struct mosaic_matrix* mat = &m1;
	float data[] = {2, 3, 2, 1, 4, 7, 5, 8, 6};
	float data2[9];
	m2.raw = data2;
	m2.rows = 3;
	m2.cols = 3;
	memcpy(m2.raw, data, 9 * sizeof(float));
	mosaic_upper_tri(&m2);
	mosaic_matrix_init(mat, data, 3, 3);
	mosaic_print(mat);
	printf("\n");
	mosaic_print(&m2);
	printf("%f\n", mosaic_determinant(mat));
}
