#include "minirt.h"

t_tuple	normal_at_plane(t_plane *plane, t_tuple world_point)
{
	(void)world_point;
	return (plane->normal);
}

t_tuple	normal_at_cylinder(t_cylinder cylinder, t_tuple point)
{
	t_tuple	pc;
	double	projection;
	t_tuple	axis_point;

	pc = tuple_subtract(point, cylinder.center);
	projection = tuple_dot(pc, cylinder.axis);
	axis_point = tuple_add(cylinder.center, tuple_multiply(cylinder.axis,
				projection));
	return (tuple_normalize(tuple_subtract(point, axis_point)));
}

void	sort_intersections(t_intersections *xs)
{
	double	temp_t;
	void	*temp_obj;
	int		i;
	int		j;

	i = 0;
	while (i < xs->count - 1)
	{
		j = 0;
		while (j < xs->count - i - 1)
		{
			if (xs->t[j] > xs->t[j + 1])
			{
				temp_t = xs->t[j];
				xs->t[j] = xs->t[j + 1];
				xs->t[j + 1] = temp_t;
				temp_obj = xs->object[j];
				xs->object[j] = xs->object[j + 1];
				xs->object[j + 1] = temp_obj;
			}
			j++;
		}
		i++;
	}
}

t_compu	prepare_computations(double t, t_ray ray, t_intersections *xs)
{
	t_compu	comps;

	comps.t = t;
	comps.object = xs->object[0];
	comps.point = position(ray, t);
	comps.eyev = tuple_negate(ray.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	if (tuple_dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = 1;
		comps.normalv = tuple_negate(comps.normalv);
	}
	else
		comps.inside = 0;
	comps.over_point = tuple_add(comps.point, tuple_multiply(comps.normalv,
				EPSILON));
	comps.reflectv = tuple_reflect(ray.direction, comps.normalv);
	return (comps);
}
