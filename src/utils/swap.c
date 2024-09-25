#include "minirt.h"

void	swap(double *a, double *b)
{
	double	temp;

	if (*a > *b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}