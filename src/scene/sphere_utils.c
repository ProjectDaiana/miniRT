#include "minirt.h"

void	calculate_sphere_params(t_ray ray, t_sphere sphere, double *params)
{
	t_tuple	sphere_to_ray;

	sphere_to_ray = tuple_subtract(ray.origin, sphere.center);
	params[0] = tuple_dot(ray.direction, ray.direction);
	params[1] = 2.0 * tuple_dot(ray.direction, sphere_to_ray);
	params[2] = tuple_dot(sphere_to_ray, sphere_to_ray) - (sphere.radius
			* sphere.radius);
}

void	init_intersection_result(t_intersections *result, double discriminant)
{
	result->count = 0;
	result->t = NULL;
	result->object = NULL;
	if (discriminant >= 0)
	{
		result->count = 2;
		result->t = malloc(sizeof(double) * 2);
		result->object = malloc(sizeof(void *) * 2);
	}
}

void	set_intersection_values(t_intersections *result, t_sphere *sphere,
		double *params)
{
	double	sqrt_disc;
	double	two_a;
	double	temp;

	sqrt_disc = sqrt(params[1] * params[1] - 4.0 * params[0] * params[2]);
	two_a = 2.0 * params[0];
	result->t[0] = (-params[1] - sqrt_disc) / two_a;
	result->t[1] = (-params[1] + sqrt_disc) / two_a;
	if (result->t[0] > result->t[1])
	{
		temp = result->t[0];
		result->t[0] = result->t[1];
		result->t[1] = temp;
	}
	result->object[0] = sphere;
	result->object[1] = sphere;
}
