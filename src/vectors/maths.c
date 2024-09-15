#include "minirt.h"

double	ft_sqr(double x)
{
	return (x * x);
}

double	vect_lenght(double x, double y, double z)
{
	return (sqrt(ft_sqr(x) + ft_sqr(y) + ft_sqr(z)));
}

double	dot_product(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_tuple	vect_addition(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_tuple	vect_subtraction(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_tuple	vect_multiplication(t_tuple a, double b)
{
	t_tuple	result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return (result);
}

double	vect_length(double x, double y, double z)
{
	return (sqrt(x * x + y * y + z * z));
}

double	cross_product_to_array(t_tuple a, t_tuple b)
{
	double	result[3];

	result[0] = a.y * b.z - a.z * b.y;
	result[1] = a.z * b.x - a.x * b.z;
	result[2] = a.x * b.y - a.y * b.x;
	printf("Cross Product: %f, %f, %f\n", result[0], result[1], result[2]);
	return (*result);
}

t_tuple	cross_product(t_tuple a, t_tuple b)
{
	t_tuple result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
