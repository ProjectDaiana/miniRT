#include "minirt.h"

int	is_invertible(double det)
{
	if (fabs(det) < EPSILON)
	{
		return (0);
	}
	return (1);
}

static void	fill_inverse_matrix(t_matrix *matrix, t_matrix *inverse,
		double determinant)
{
	int		i;
	int		j;
	double	cofactor;

	i = 0;
	while (i < matrix->size)
	{
		j = 0;
		while (j < matrix->size)
		{
			cofactor = calculate_cofactor(matrix, i, j, matrix->size);
			inverse->m[j][i] = cofactor / determinant;
			j++;
		}
		i++;
	}
}

t_matrix	inverse_matrix(t_matrix *matrix)
{
	t_matrix	inverse;
	double		determinant;
	int			size;

	size = matrix->size;
	inverse = create_matrix(size);
	determinant = calculate_determinant(matrix, size);
	if (!is_invertible(determinant))
		return (create_identity_matrix());
	fill_inverse_matrix(matrix, &inverse, determinant);
	return (inverse);
}
