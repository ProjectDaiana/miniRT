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