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

t_intersections	intersect_cylinder(t_cylinder cylinder, t_ray ray)
{
	t_intersections	result;
	t_tuple			oc;
	double			a;
	double			b;
	double			c;
	double			discriminant;
	double			t1;
	double			t2;
	double			y1;
	double			y2;
	int				index;

	result.count = 0;
	result.t1 = 0;
	result.t2 = 0;
	oc = tuple_subtract(ray.origin, cylinder.center);
	a = tuple_dot(ray.direction, ray.direction) - pow(tuple_dot(ray.direction,
				cylinder.axis), 2);
	b = 2 * (tuple_dot(ray.direction, oc) - tuple_dot(ray.direction,
				cylinder.axis) * tuple_dot(oc, cylinder.axis));
	c = tuple_dot(oc, oc) - pow(tuple_dot(oc, cylinder.axis), 2)
		- pow(cylinder.diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0) // then calculate t1 and t2 and check if they are within the bounds of the cylinder 
	{
		t1 = (-b - sqrt(discriminant)) / (2 * a);
		t2 = (-b + sqrt(discriminant)) / (2 * a);
		swap(&t1, &t2);
		/////
		double origin_projection = tuple_dot(ray.origin, cylinder.axis);
		double direction_projection = tuple_dot(ray.direction, cylinder.axis);
		y1 = origin_projection + t1 * direction_projection;
		y2 = origin_projection + t2 * direction_projection;
		// y1 = ray.origin.y + t1 * ray.direction.y;
		// y2 = ray.origin.y + t2 * ray.direction.y;
		if (y1 < cylinder.min || y1 > cylinder.max)
			t1 = INFINITY;
		if (y2 < cylinder.min || y2 > cylinder.max)
			t2 = INFINITY;
		result.count = (t1 != INFINITY) + (t2 != INFINITY);
		result.t = malloc(sizeof(double) * result.count);
		result.object = malloc(sizeof(void *) * result.count);
		index = 0;
		if (t1 != INFINITY)
		{
			result.t[index] = t1;
			result.object[index] = &cylinder;
			index++;
		}
		if (t2 != INFINITY)
		{
			result.t[index] = t2;
			result.object[index] = &cylinder;
		}
	}
	intersect_caps(cylinder, ray, &result);
	return (result);
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
