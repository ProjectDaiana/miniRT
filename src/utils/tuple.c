#include "minirt.h"

t_tuple	create_tuple(double x, double y, double z, double w)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = w;
	return (tuple);
}

t_tuple	create_point(double x, double y, double z)
{
	return (create_tuple(x, y, z, 1.0));
}

t_tuple	create_vector(double x, double y, double z)
{
	return (create_tuple(x, y, z, 0.0));
}

t_tuple	tuple_add(t_tuple a, t_tuple b)
{
	return (create_tuple(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
}

t_tuple	tuple_subtract(t_tuple a, t_tuple b)
{
	return (create_tuple(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w));
}

t_tuple	tuple_negate(t_tuple a)
{
	return (create_tuple(-a.x, -a.y, -a.z, -a.w));
}

t_tuple	tuple_multiply(t_tuple a, double scalar)
{
	return (create_tuple(a.x * scalar, a.y * scalar, a.z * scalar, a.w
			* scalar));
}

t_tuple	tuple_divide(t_tuple a, double scalar)
{
	return (create_tuple(a.x / scalar, a.y / scalar, a.z / scalar, a.w
			/ scalar));
}

double	tuple_magnitude(t_tuple a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w));
}

t_tuple	tuple_normalize(t_tuple a)
{
	double	mag;

	mag = tuple_magnitude(a);
	return (tuple_divide(a, mag));
}

double	tuple_dot(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

t_tuple	tuple_cross(t_tuple a, t_tuple b)
{
	return (create_vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x
			* b.y - a.y * b.x));
}

t_tuple	tuple_reflect(t_tuple in, t_tuple normal)
{
	return (tuple_subtract(in, tuple_multiply(normal, 2 * tuple_dot(in,
					normal))));
}
