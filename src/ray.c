#include "minirt.h"

// Ray	create_ray(double x, double y)
// {
// 	Ray		ray;
// 	double	length;

// 	ray.origin = (t_vector){0, 0, -5};
// 	ray.direction = (t_vector){x - 0.5, y - 0.5, 1};
// 	// Normalize ray direction
// 	length = sqrt(ray.direction.x * ray.direction.x + ray.direction.y
// 			* ray.direction.y + ray.direction.z * ray.direction.z);
// 	ray.direction.x /= length;
// 	ray.direction.y /= length;
// 	ray.direction.z /= length;
// 	return (ray);
// }

Ray	create_ray(double x, double y)
{
	Ray	ray;

	ray.origin = (t_vector){0, 2, -5}; // Camera position
	ray.direction = vect_normalize((t_vector){x - 0.5, (y - 0.5) * -1, 1});
	return (ray);
}

// t_hit	intersect_sphere(Ray ray, t_sphere sphere)
// {
// 	t_hit		hit;
// 	t_vector	oc;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;
// 	double		t1;
// 	double		t2;

// 	hit = (t_hit){0};
// 	oc = vect_subtraction(ray.origin, sphere.center);
// 	a = dot_product(ray.direction, ray.direction);
// 	b = 2.0 * dot_product(oc, ray.direction);
// 	c = dot_product(oc, oc) - sphere.radius * sphere.radius;
// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 	{
// 		hit.hit = 0;
// 		return (hit);
// 	}
// 	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
// 	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
// 	hit.hit = 1;
// 	hit.t = (t1 < t2 && t1 > 0) ? t1 : t2;
// 	hit.point = vect_addition(ray.origin, vect_multiplication(ray.direction,
// 				hit.t));
// 	hit.normal = vect_normalize(vect_subtraction(hit.point, sphere.center));
// 	return (hit);
// }

// int	trace_ray(Ray ray)
// {
// 	Sphere	sphere;
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	discriminant;
// 	int		check_x;
// 	int		check_y;

// 	sphere.center = (t_vector){0, 0, 0};
// 	sphere.radius = 1;
// 	// Ray-sphere intersection
// 	a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y
// 		+ ray.direction.z * ray.direction.z;
// 	b = 2 * (ray.direction.x * (ray.origin.x - sphere.center.x)
// 			+ ray.direction.y * (ray.origin.y - sphere.center.y)
// 			+ ray.direction.z * (ray.origin.z - sphere.center.z));
// 	c = (ray.origin.x - sphere.center.x) * (ray.origin.x - sphere.center.x)
// 		+ (ray.origin.y - sphere.center.y) * (ray.origin.y - sphere.center.y)
// 		+ (ray.origin.z - sphere.center.z) * (ray.origin.z - sphere.center.z)
// 		- sphere.radius * sphere.radius;
// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant >= 0)
// 	{
// 		// Ray hits the sphere
// 		return (0xFF0000); // Red color
// 	}
// 	// Ray misses the sphere, draw checkered background
// 	check_x = (int)(ray.direction.x * 10) & 1;
// 	check_y = (int)(ray.direction.y * 10) & 1;
// 	if (check_x ^ check_y)
// 	{
// 		return (0xFFFFFF); // White
// 	}
// 	return (0x000000); // Black
// }

t_color	trace_ray(Ray ray, t_scene *scene)
{
	t_hit		hit;
	t_color		color;
	Ray			reflect_ray;
	t_color		reflect_color;
	double		check_size;
	double		t;
	t_vector	point;
	int			check_x;
	int			check_z;
	int			check_y;

	check_size = 1.0;
	hit = intersect_sphere(ray, scene->sphere);
	if (hit.hit)
	{
		color = calculate_lighting(hit, scene, ray);
		if (scene->sphere.material.reflective > 0)
		{
			reflect_ray.origin = hit.point;
			reflect_ray.direction = vect_reflect(ray.direction, hit.normal);
			reflect_color = trace_ray(reflect_ray, scene);
			color = add_color(color, multiply_color_by_scalar(reflect_color,
						scene->sphere.material.reflective));
		}
		return (color);
	}
	// Checkered floor and walls
	t = -ray.origin.y / ray.direction.y;
	if (t > 0)
	{
		point = vect_addition(ray.origin, vect_multiplication(ray.direction,
					t));
		check_x = (int)(point.x / check_size) & 1;
		check_z = (int)(point.z / check_size) & 1;
		if (check_x ^ check_z)
			return ((t_color){255, 255, 255}); // White
		else
			return ((t_color){0, 0, 0}); // Black
	}
	// Walls
	t = (5 - ray.origin.z) / ray.direction.z;
	if (t > 0)
	{
		point = vect_addition(ray.origin, vect_multiplication(ray.direction,
					t));
		check_x = (int)(point.x / check_size) & 1;
		check_y = (int)(point.y / check_size) & 1;
		if (check_x ^ check_y)
			return ((t_color){255, 255, 255}); // White
		else
			return ((t_color){0, 0, 0}); // Black
	}
	return ((t_color){100, 100, 100}); // Gray background
}
