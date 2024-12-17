#include "minirt.h"

t_intersections	intersect_plane(t_plane plane, t_ray ray)
{
	double			denom;
	t_tuple			p0l0;
	double			t;
	t_intersections	result;

	result.count = 0;
	result.t1 = 0;
	result.t2 = 0;
	denom = tuple_dot(plane.normal, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		p0l0 = tuple_subtract(plane.point, ray.origin);
		t = tuple_dot(p0l0, plane.normal) / denom;
		if (t >= 0)
		{
			result.count = 1;
			result.t = malloc(sizeof(double));
			result.t[0] = t;
			result.object = malloc(sizeof(void *));
			result.object[0] = &plane;
		}
	}
	return (result);
}

// t_intersections	intersect_cylinder(t_cylinder cylinder, t_ray ray)
// {
// 	t_intersections	result;
// 	double			t[2];
// 	double			y[2];

// 	init_cylinder_intersection(&result);
// 	calculate_cylinder_intersections(cylinder, ray, t, y);
// 	check_cylinder_bounds(cylinder, t, y);
// 	allocate_intersections(&result, t, &cylinder);
// 	return (result);
// }

static void	add_sphere_intersections(t_scene *scene, t_ray ray,
		t_intersections *result)
{
	t_intersections	sphere_xs;
	int				i;
	int				j;

	i = 0;
	while (i < scene->sphere_count)
	{
		sphere_xs = intersect_sphere(scene->spheres[i], ray);
		j = 0;
		while (j < sphere_xs.count)
		{
			result->t[result->count] = sphere_xs.t[j];
			result->object[result->count] = &scene->spheres[i];
			result->count++;
			j++;
		}
		i++;
	}
}

static void	add_plane_intersections(t_scene *scene, t_ray ray,
		t_intersections *result)
{
	t_intersections	plane_xs;
	int				i;
	int				j;

	i = 0;
	while (i < scene->plane_count)
	{
		plane_xs = intersect_plane(scene->planes[i], ray);
		j = 0;
		while (j < plane_xs.count)
		{
			result->t[result->count] = plane_xs.t[j];
			result->object[result->count] = &scene->planes[i];
			result->count++;
			j++;
		}
		i++;
	}
}

t_intersections	intersect_world(t_scene *scene, t_ray ray)
{
	t_intersections	result;
	int				max_intersections;

	result.count = 0;
	result.t = NULL;
	result.object = NULL;
	max_intersections = scene->sphere_count * 2 + scene->plane_count;
	result.t = malloc(sizeof(double) * max_intersections);
	result.object = malloc(sizeof(void *) * max_intersections);
	add_sphere_intersections(scene, ray, &result);
	add_plane_intersections(scene, ray, &result);
	sort_intersections(&result);
	return (result);
}
