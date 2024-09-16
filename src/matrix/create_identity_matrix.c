#include "minirt.h"

t_matrix	create_identity_matrix(void)
{
	t_matrix identity;
	identity = create_matrix(4);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			identity.m[i][j] = (i == j) ? 1.0 : 0.0;
		}
	}
	return (identity);
}