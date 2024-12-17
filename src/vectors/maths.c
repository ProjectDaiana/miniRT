#include "minirt.h"

double	ft_sqr(double x)
{
	return (x * x);
}

t_vector	vect_addition(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector	vect_multiplication(t_vector a, double b)
{
	t_vector	result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return (result);
}
