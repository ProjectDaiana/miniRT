#include "minirt.h"

t_sphere	create_sphere(void)
{
	t_sphere	sphere;

	sphere.center = create_point(0, 0, 0);
	sphere.radius = 1.0;
	return (sphere);
}
// ok

// t_intersections	intersect_sphere(t_sphere sphere, t_ray ray)
// {
// 	t_intersections	result;
// 	t_tuple			sphere_to_ray;
// 	double			a;
// 	double			b;
// 	double			c;
// 	double			discriminant;

// 	sphere_to_ray = tuple_subtract(ray.origin, sphere.center);
// 	a = tuple_dot(ray.direction, ray.direction);
// 	b = 2 * tuple_dot(ray.direction, sphere_to_ray);
// 	c = tuple_dot(sphere_to_ray, sphere_to_ray) - sphere.radius * sphere.radius;
// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 	{
// 		result.count = 0;
// 	}
// 	else
// 	{
// 		result.count = 2;
// 		result.t = malloc(2 * sizeof(double));
// 		result.object = malloc(2 * sizeof(void *));
// 		result.t[0] = (-b - sqrt(discriminant)) / (2 * a);
// 		result.t[1] = (-b + sqrt(discriminant)) / (2 * a);
// 		result.object[0] = result.object[1] = &sphere;
// 	}
// 	return (result);
// }

t_intersections	intersect_sphere(t_sphere sphere, t_ray ray)
{
	t_intersections	result;
	t_tuple			sphere_to_ray;
	double			sqrt_discriminant;
	double			two_a;

	double a, b, c, discriminant;
	// Initialize result
	result.count = 0;
	result.t = NULL;
	result.object = NULL;
	// Calculate vector from sphere center to ray origin
	sphere_to_ray = tuple_subtract(ray.origin, sphere.center);
	// Calculate quadratic equation coefficients
	a = tuple_dot(ray.direction, ray.direction);
	// Should be 1 if ray direction is normalized
	b = 2.0 * tuple_dot(ray.direction, sphere_to_ray);
	c = tuple_dot(sphere_to_ray, sphere_to_ray) - (sphere.radius
			* sphere.radius);
	// Calculate discriminant
	discriminant = (b * b) - (4.0 * a * c);
	if (discriminant >= 0)
	{
		result.count = 2;
		result.t = malloc(sizeof(double) * 2);
		result.object = malloc(sizeof(void *) * 2);
		sqrt_discriminant = sqrt(discriminant);
		two_a = 2.0 * a;
		result.t[0] = (-b - sqrt_discriminant) / two_a;
		result.t[1] = (-b + sqrt_discriminant) / two_a;
		result.object[0] = &sphere;
		result.object[1] = &sphere;
		// Debug print
		printf("Intersection points found: t1=%f, t2=%f\n", result.t[0],
			result.t[1]);
	}
	return (result);
}

// t_tuple	normal_at(t_sphere sphere, t_tuple world_point)
// {
// 	t_tuple	object_point;
// 	t_tuple	object_normal;

// 	object_point = tuple_subtract(world_point, sphere.center);
// 	object_normal = tuple_normalize(object_point);
// 	return (object_normal);
// }

// t_tuple	normal_at_sphere(t_sphere sphere, t_tuple world_point)
// {
// 	t_tuple	object_point;
// 	t_tuple	object_normal;
// 	t_tuple	world_normal;

// 	object_point = tuple_subtract(world_point, sphere.center);
// 	object_normal = tuple_normalize(object_point);
// 	world_normal = object_normal;
// 	world_normal.w = 0;
// 	return (world_normal);
// }

t_tuple	normal_at_sphere(t_sphere *sphere, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;

	object_point = tuple_subtract(world_point, sphere->center);
	object_normal = tuple_normalize(object_point);
	t_tuple world_normal = object_normal; // For spheres,
	world_normal.w = 0;                   // Ensure it's a vector, not a point
	return (world_normal);
}

// ok
// t_tuple	normal_at(void *object, t_tuple world_point)
// {
// 	if (((t_sphere *)object)->radius > 0) // It's a sphere
// 	{
// 		return (normal_at_sphere((t_sphere *)object, world_point));
// 	}
// 	else if (((t_plane *)object)->normal.x != 0
// 		|| ((t_plane *)object)->normal.y != 0
// 		|| ((t_plane *)object)->normal.z != 0) // It's a plane
// 	{
// 		return (normal_at_plane((t_plane *)object, world_point));
// 	}
// 	// Add more conditions for other object types as needed

// 	// Default case (should not happen)
// 	return (create_vector(0, 0, 0));
// }

t_tuple	normal_at(void *object, t_tuple world_point)
{
	if (((t_sphere *)object)->radius > 0) // It's a sphere
	{
		return (normal_at_sphere((t_sphere *)object, world_point));
	}
	else if (((t_plane *)object)->normal.x != 0
		|| ((t_plane *)object)->normal.y != 0
		|| ((t_plane *)object)->normal.z != 0) // It's a plane
	{
		return (normal_at_plane((t_plane *)object, world_point));
	}
	// Add more conditions for other object types as needed

	// Default case (should not happen)
	return (create_vector(0, 0, 0));
}
