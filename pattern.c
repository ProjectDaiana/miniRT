#include "minirt.h"

t_color	stripe_pattern(t_pattern pattern, t_tuple point)
{
	int	x;

	x = floor(point.x);
	return ((x % 2 == 0) ? pattern.a : pattern.b);
}

t_color	checker_pattern(t_pattern pattern, t_tuple point)
{
	int	sum;

	sum = floor(point.x) + floor(point.y) + floor(point.z);
	return ((sum % 2 == 0) ? pattern.a : pattern.b);
}

t_color	pattern_at(t_pattern pattern, t_tuple point)
{
	switch (pattern.type)
	{
	case STRIPE:
		return (stripe_pattern(pattern, point));
	case CHECKER:
		return (checker_pattern(pattern, point));
	default:
		return (create_color(0, 0, 0));
	}
}