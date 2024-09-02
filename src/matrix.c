#include "minirt.h"

//Create matrix
t_matrix create_matrix(double m[4][4])
{
	t_matrix matrix;

	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			matrix.m[i][j] = m[i][j];
			j++;
		}
		i++;
	}
	return (matrix);
}

void print_matrix(t_matrix matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%f ", matrix.m[i][j]);
		printf("\n");
	}
}

int	compare_matrix(t_matrix a, t_matrix b)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (a.m[i][j] != b.m[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

//Multiply matrix by matrix. This is similar to the dot product of two vectors
t_matrix matrix_multiply(t_matrix a, t_matrix b)
{
	t_matrix result;
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];
			j++;
		}
		i++;
	}
	return (result);
}

t_tuple multiply_matrix_by_tuple(t_matrix *matrix, t_tuple *tuple)
{
    t_tuple result;

    result.x = matrix->m[0][0] * tuple->x + matrix->m[0][1] * tuple->y + matrix->m[0][2] * tuple->z + matrix->m[0][3] * tuple->w;
    result.y = matrix->m[1][0] * tuple->x + matrix->m[1][1] * tuple->y + matrix->m[1][2] * tuple->z + matrix->m[1][3] * tuple->w;
    result.z = matrix->m[2][0] * tuple->x + matrix->m[2][1] * tuple->y + matrix->m[2][2] * tuple->z + matrix->m[2][3] * tuple->w;
    result.w = matrix->m[3][0] * tuple->x + matrix->m[3][1] * tuple->y + matrix->m[3][2] * tuple->z + matrix->m[3][3] * tuple->w;

    return result;
}