#include "minirt.h"

void print_matrix(t_matrix matrix, char *str, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf(YEL"%s\n"RESET ,str);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			printf("%f ", matrix.m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
