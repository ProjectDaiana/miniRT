# include "minirt.h"

double ft_sqr (double x)
{
	return (x * x);
}

double vect_lenght(double x, double y, double z)
{
	return sqrt(ft_sqr(x) + ft_sqr(y) + ft_sqr(z));
}

double dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double vect_length(double x, double y, double z) {
    return sqrt(x*x + y*y + z*z);
}

// double cross_product(t_vector a, t_vector b)
// {
// 	t_vector result;

// 	result.x = a.y * b.z - a.z * b.y;
// 	result.y = a.z * b.x - a.x * b.z;
// 	result.z = a.x * b.y - a.y * b.x;
// 	return (result);
// }

double cross_product_to_array(t_vector a, t_vector b)
{
	double result[3];
	result[0] = a.y * b.z - a.z * b.y;
	result[1] = a.z * b.x - a.x * b.z;
	result[2] = a.x * b.y - a.y * b.x;
	return (*result);
}