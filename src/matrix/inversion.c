#include "minirt.h"

int is_invertible(double det)
{
	if (det == 0)
	{
		printf(RED"Matrix is not invertible\n"RESET);
		exit(1);
	}
	return (1);
}

// Inversion Reverts the effect of multipliyin by a matrix. NOT ALL MATRICES ARE INVERTIBLE!
// BUG ALERT! It prints a double with 1 more number than in the test which seems to round -0.538462 to -0.53846
t_matrix inverse_matrix(t_matrix *matrix)
{
	t_matrix inverse;
	double determinant;
	int i;
	int j;
	// double cofactor;
	double minor;
	int sign;
	int size;

	size = matrix->size;
	inverse = create_matrix(size);
	determinant = calculate_determinant(matrix, size);
	is_invertible(determinant);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			sign = (i + j) % 2 == 0 ? 1 : -1;
			minor = calculate_minor(matrix, i, j, size);
			// cofactor = calculate_cofactor(matrix, i, j, size);
			inverse.m[j][i] = sign * minor / determinant;
			j++;
		}
		i++;
	}
	return (inverse);
}