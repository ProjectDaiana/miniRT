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

t_tuple	normal_at_plane(t_plane plane, t_tuple point)
{
	(void)point;
	return (plane.normal);
}

void	sort_intersections(t_intersections *xs)
{
	double	temp_t;
	void	*temp_obj;

	for (int i = 0; i < xs->count - 1; i++)
	{
		for (int j = 0; j < xs->count - i - 1; j++)
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
		}
	}
}

t_intersections	intersect_world(t_scene *scene, t_ray ray)
{
	t_intersections	result;
	int				max_intersections;
	t_intersections	sphere_xs;
	t_intersections	plane_xs;
	t_intersections	cylinder_xs;

	result.count = 0;
	result.t = NULL;
	result.object = NULL;
	// Allocate initial memory
	max_intersections = scene->sphere_count * 2 + scene->plane_count
		+ scene->cylinder_count * 2;
	result.t = malloc(sizeof(double) * max_intersections);
	result.object = malloc(sizeof(void *) * max_intersections);
	// Intersect with spheres
	for (int i = 0; i < scene->sphere_count; i++)
	{
		sphere_xs = intersect_sphere(scene->spheres[i], ray);
		for (int j = 0; j < sphere_xs.count; j++)
		{
			result.t[result.count] = sphere_xs.t[j];
			result.object[result.count] = &scene->spheres[i];
			result.count++;
		}
	}
	// Intersect with planes
	for (int i = 0; i < scene->plane_count; i++)
	{
		plane_xs = intersect_plane(scene->planes[i], ray);
		for (int j = 0; j < plane_xs.count; j++)
		{
			result.t[result.count] = plane_xs.t[j];
			result.object[result.count] = &scene->planes[i];
			result.count++;
		}
	}
	// Intersect with cylinders
	for (int i = 0; i < scene->cylinder_count; i++)
	{
		cylinder_xs = intersect_cylinder(scene->cylinders[i], ray);
		for (int j = 0; j < cylinder_xs.count; j++)
		{
			result.t[result.count] = cylinder_xs.t[j];
			result.object[result.count] = &scene->cylinders[i];
			result.count++;
		}
	}
	// Sort intersections
	sort_intersections(&result);
	return (result);
}
