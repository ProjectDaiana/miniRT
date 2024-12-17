#include "minirt.h"

void	init_cylinder_intersection(t_intersections *result)
{
	result->count = 0;
	result->t1 = 0;
	result->t2 = 0;
}

void	calculate_cylinder_params(t_cylinder cylinder, t_ray ray,
		double *params)
{
	t_tuple	oc;

	oc = tuple_subtract(ray.origin, cylinder.center);
	params[0] = tuple_dot(ray.direction, ray.direction)
		- pow(tuple_dot(ray.direction, cylinder.axis), 2);
	params[1] = 2 * (tuple_dot(ray.direction, oc) - tuple_dot(ray.direction,
				cylinder.axis) * tuple_dot(oc, cylinder.axis));
	params[2] = tuple_dot(oc, oc) - pow(tuple_dot(oc, cylinder.axis), 2)
		- pow(cylinder.diameter / 2, 2);
}

void	add_valid_intersection(t_intersections *result, double t,
		t_cylinder *cylinder, int *index)
{
	result->t[*index] = t;
	result->object[*index] = cylinder;
	(*index)++;
}

// void	calculate_cylinder_intersections(t_cylinder cylinder, t_ray ray,
// 		double *t, double *y)
// {
// 	double	params[3];

// 	calculate_cylinder_params(cylinder, ray, params);
// 	if (params[1] * params[1] - 4 * params[0] * params[2] >= 0)
// 	{
// 		t[0] = (-params[1] - sqrt(params[1] * params[1] - 4 * params[0]
// 					* params[2])) / (2 * params[0]);
// 		t[1] = (-params[1] + sqrt(params[1] * params[1] - 4 * params[0]
// 					* params[2])) / (2 * params[0]);
// 		y[0] = ray.origin.y + t[0] * ray.direction.y;
// 		y[1] = ray.origin.y + t[1] * ray.direction.y;
// 	}
// 	else
// 	{
// 		t[0] = INFINITY;
// 		t[1] = INFINITY;
// 	}
// }

// void	check_cylinder_bounds(t_cylinder cylinder, double *t, double *y)
// {
// 	if (y[0] < cylinder.center.y || y[0] > cylinder.center.y + cylinder.height)
// 		t[0] = INFINITY;
// 	if (y[1] < cylinder.center.y || y[1] > cylinder.center.y + cylinder.height)
// 		t[1] = INFINITY;
// }
