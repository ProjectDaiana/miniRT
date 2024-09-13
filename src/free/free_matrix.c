#include "minirt.h"

void	free_matrix(t_matrix *matrix)
{
	int i;

	i = 0;
	while (i < matrix->size)
	{
		free(matrix->m[i]);
		i++;
	}
	free(matrix->m);
}