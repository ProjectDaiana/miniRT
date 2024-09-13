#include "minirt.h"

t_ray	create_ray(double x, double y)
{
	t_ray	ray;

	ray.origin = (t_tuple){0, 2, -5, 0}; // Camera position
	ray.direction = normalize_vect((t_tuple){x - 0.5, (y - 0.5) * -1, 1, 1});
	return (ray);
}

t_ray ray(t_tuple *origin, t_tuple *direction)
{
	t_ray ray;

	ray.origin = *origin;
	ray.direction = *direction;
	return (ray);
}



// t_color	trace_ray(t_ray ray, t_scene *scene)
// {
// 	t_hit		hit;
// 	t_color		color;
// 	t_ray		reflect_ray;
// 	t_color		reflect_color;
// 	double		check_size;
// 	double		t;
// 	t_tuple	point;
// 	int			check_x;
// 	int			check_z;
// 	int			check_y;

// 	check_size = 1.0;
// 	check_z = 0;
// 	// hits sphere?
// 	hit = intersect_sphere(ray, scene->sphere);
// 	if (hit.hit)
// 	{
// 		color = calculate_lighting(hit, scene, ray);
// 		if (scene->sphere.material.reflective > 0)
// 		{
// 			reflect_ray.origin = hit.point;
// 			reflect_ray.direction = vect_reflect(ray.direction, hit.normal);
// 			reflect_color = trace_ray(reflect_ray, scene);
// 			color = add_color(color, multiply_color_by_scalar(reflect_color,
// 						scene->sphere.material.reflective));
// 		}
// 		return (color);
// 	}
// 	// hits floor?
// 	t = -ray.origin.y / ray.direction.y;
// 	if (t > 0)
// 	{
// 		point = vect_addition(ray.origin, vect_multiplication(ray.direction,
// 					t));
// 		check_x = (int)(point.x / check_size) & 1;
// 		check_z = (int)(point.z / check_size) & 1;
// 		if ((check_x == 1 && check_z == 0) || (check_x == 0 && check_z == 1))
// 			return ((t_color){255, 255, 255}); // White
// 		else
// 			return ((t_color){0, 0, 0}); // Black
// 	}
// 	// hits wall?
// 	t = (-ray.origin.z) / ray.direction.z;
// 	if (t > 0) // will not hit the wall at <= 0
// 	{
// 		point = vect_addition(ray.origin, vect_multiplication(ray.direction,
// 					t));
// 		check_x = (int)(point.x / check_size) & 1;
// 		check_y = (int)(point.y / check_size) & 1;
// 		if ((check_x == 1 && check_y == 0) || (check_x == 0 && check_y == 1))
// 			return ((t_color){255, 255, 255}); // White
// 		else
// 			return ((t_color){0, 0, 0}); // Black
// 	}
// 	return ((t_color){0, 0, 0});
// 	// t = (5 - ray.origin.z) / ray.direction.z;
// 	// 	if (t > 0) // will not hit the wall at <= 0
// 	// 	{
// 	// 		point = vect_addition(ray.origin, vect_multiplication(ray.direction,
// 	// 					t));
// 	// 		check_x = (int)(point.x / check_size) & 1;
// 	// 		check_y = (int)(point.y / check_size) & 1;
// 	// 		if ((check_x == 1 && check_z == 0) || (check_x == 0
// 					&& check_z == 1))
// 	// 			return ((t_color){255, 255, 255}); // White
// 	// 		else
// 	// 			return ((t_color){0, 0, 0}); // Black
// 	// 	}
// 	// 	return ((t_color){0, 0, 0});
// }

t_hit	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_hit		hit;
	t_tuple	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t;

	oc = vect_subtraction(ray.origin, sphere.center);
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	hit.hit = 0;
	if (discriminant >= 0)
	{
		t = (-b - sqrt(discriminant)) / (2.0 * a);
		if (t > 0)
		{
			hit.hit = 1;
			hit.t = t;
			hit.point = vect_addition(ray.origin,
					vect_multiplication(ray.direction, t));
			hit.normal = normalize_vect(vect_subtraction(hit.point,
						sphere.center));///Changed this from vect_normalize to normalize_vect
			hit.material = sphere.material;
		}
	}
	return (hit);
}

t_color	trace_ray(t_ray ray, t_scene *scene)
{
	t_hit hit;
	t_color color;
	double closest_t;
	t_hit current_hit;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	closest_t = INFINITY;
	for (int i = 0; i < scene->sphere_count; i++)
	{
		current_hit = intersect_sphere(ray, scene->spheres[i]);
		if (current_hit.hit && current_hit.t < closest_t)
		{
			hit = current_hit;
			closest_t = current_hit.t;
			color = calculate_lighting(hit, scene, ray);
			printf("Hit sphere %d at t=%f\n", i, hit.t);
		}
	}
	if (closest_t == INFINITY)
	{
		// No hit, return background color
		color = (t_color){50, 50, 50}; // Dark gray background
	}
	return (color);
}