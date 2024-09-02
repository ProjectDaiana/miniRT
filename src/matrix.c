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