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

