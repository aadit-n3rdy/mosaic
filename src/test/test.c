#include <mosaic.h>
#include <stdio.h>

int main() {
	struct mosaic_matrix m1;
	struct mosaic_matrix m2;
	struct mosaic_matrix result;
	mosaic_matrix_init(&m1, 2, 3);
	mosaic_matrix_init(&m2, 3, 2);
	mosaic_matrix_init(&result, 2, 2);
	float data[] = {1, 2, 3, 4, 5, 6};
	mosaic_matrix_assign(&m1, data);
	mosaic_matrix_assign(&m2, data);
	mosaic_matrix_multiply(&m1, &m2, &result);
	printf("%f %f %f %f\n", result.raw[0], result.raw[1], result.raw[2], result.raw[3]);
	return 0;
}
