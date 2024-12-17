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
