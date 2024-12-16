#include "minirt.h"

// int	is_invertible(double det)
// {
// 	if (det == 0)
// 	{
// 		printf(RED "Matrix is not invertible\n" RESET);
// 		exit(1);
// 	}
// 	return (1);
// }

int	is_invertible(double det)
{
	if (fabs(det) < EPSILON)
	{
		return (0);
	}
	return (1);
}

// Inversion Reverts the effect of multipliyin by a matrix. NOT ALL MATRICES ARE INVERTIBLE!

// t_matrix	inverse_matrix(t_matrix *matrix)
// {
// 	t_matrix	inverse;
// 	double		determinant;
// 	int			i;
// 	int			j;
// 	double		cofactor;
// 	int			size;

// 	size = matrix->size;
// 	inverse = create_matrix(size);
// 	determinant = calculate_determinant(matrix, size);
// 	is_invertible(determinant);
// 	i = 0;
// 	while (i < size)
// 	{
// 		j = 0;
// 		while (j < size)
// 		{
// 			cofactor = calculate_cofactor(matrix, i, j, size);
// 			inverse.m[j][i] = cofactor / determinant;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (inverse);
// }

t_matrix	inverse_matrix(t_matrix *matrix)
{
	t_matrix inverse;
	double determinant;
	int i, j;
	double cofactor;
	int size;

	size = matrix->size;
	inverse = create_matrix(size);
	determinant = calculate_determinant(matrix, size);
	if (!is_invertible(determinant))
	{
		// Return the identity matrix if the matrix is not invertible
		return (create_identity_matrix());
	}
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			cofactor = calculate_cofactor(matrix, i, j, size);
			inverse.m[j][i] = cofactor / determinant;
			j++;
		}
		i++;
	}
	return (inverse);
}