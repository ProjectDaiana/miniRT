#include "minirt.h"

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
