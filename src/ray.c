#include "minirt.h"

// t_ray	create_ray(double x, double y)
// {
// 	t_ray	ray;

// 	ray.origin = (t_vector){0, 2, -5}; // Camera position
// 	ray.direction = vect_normalize((t_vector){x - 0.5, (y - 0.5) * -1, 1});
// 	return (ray);
// }

t_ray	create_ray(double x, double y, t_camera *camera)
{
	t_ray		ray;
	t_matrix	camera_transform;

	// Create camera transformation matrix
	camera_transform = create_identity_matrix();
	camera_transform = matrix_multiply(create_rotation_x_matrix(camera->orientation.x),
			camera_transform);
	camera_transform = matrix_multiply(create_rotation_y_matrix(camera->orientation.y),
			camera_transform);
	camera_transform = matrix_multiply(create_rotation_z_matrix(camera->orientation.z),
			camera_transform);
	camera_transform = matrix_multiply(create_translation_matrix(camera->position.x,
				camera->position.y, camera->position.z), camera_transform);
	// Create ray origin and direction in camera space
	ray.origin = (t_vector){0, 0, 0};
	ray.direction = vect_normalize((t_vector){(2 * x - 1) * tan(camera->fov
				/ 2), (1 - 2 * y) * tan(camera->fov / 2), -1});
	// Transform ray to world space
	ray.origin = apply_matrix_to_vector(camera_transform, ray.origin);
	ray.direction = apply_matrix_to_vector(camera_transform, ray.direction);
	ray.direction = vect_normalize(ray.direction);
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
// 	t_vector	point;
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
	t_vector	oc;
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
			hit.normal = vect_normalize(vect_subtraction(hit.point,
						sphere.center));
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