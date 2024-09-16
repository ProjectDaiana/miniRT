#include "minirt.h"

// t_ray	create_ray(double x, double y)
// {
// 	t_ray	ray;

// 	ray.origin = (t_tuple){0, 2, -5}; // Camera position
// 	ray.direction = normalize_vect((t_tuple){x - 0.5, (y - 0.5) * -1, 1});
// 	return (ray);
// }

t_ray ray(t_tuple *origin, t_tuple *direction)
{
	t_ray ray;

	ray.origin = *origin;
	ray.direction = *direction;
	return (ray);
}



// t_hit	intersect_sphere(t_ray ray, t_sphere sphere)
// {
// 	t_hit		hit;
// 	t_tuple	oc;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;
// 	double		t;

// 	oc = vect_subtraction(ray.origin, sphere.center);
// 	a = dot_product(ray.direction, ray.direction);
// 	b = 2.0 * dot_product(oc, ray.direction);
// 	c = dot_product(oc, oc) - sphere.radius * sphere.radius;
// 	discriminant = b * b - 4 * a * c;
// 	hit.hit = 0;
// 	if (discriminant >= 0)
// 	{
// 		t = (-b - sqrt(discriminant)) / (2.0 * a);
// 		if (t > 0)
// 		{
// 			hit.hit = 1;
// 			hit.t = t;
// 			hit.point = vect_addition(ray.origin,
// 					vect_multiplication(ray.direction, t));
// 			hit.normal = normalize_vect(vect_subtraction(hit.point,
// 						sphere.center));///Changed this from vect_normalize to normalize_vect
// 			hit.material = sphere.material;
// 		}
// 	}
// 	return (hit);
// }

// t_color	trace_ray(t_ray ray, t_scene *scene)
// {
// 	t_hit hit;
// 	t_color color;
// 	double closest_t;
// 	t_hit current_hit;

// 	color.r = 0;
// 	color.g = 0;
// 	color.b = 0;
// 	closest_t = INFINITY;
// 	for (int i = 0; i < scene->sphere_count; i++)
// 	{
// 		current_hit = intersect_sphere(ray, scene->spheres[i]);
// 		if (current_hit.hit && current_hit.t < closest_t)
// 		{
// 			hit = current_hit;
// 			closest_t = current_hit.t;
// 			color = calculate_lighting(hit, scene, ray);
// 			printf("Hit sphere %d at t=%f\n", i, hit.t);
// 		}
// 	}
// 	if (closest_t == INFINITY)
// 	{
// 		// No hit, return background color
// 		color = (t_color){50, 50, 50}; // Dark gray background
// 	}
// 	return (color);
// }

t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = normalize_vect(direction);
	printf("create ray origin %f %f %f %f",origin.x, origin.y, origin.z, origin.w);
	printf("create ray origin %f %f %f %f",direction.x, direction.y, direction.z, direction.w);

	return (ray);
}

t_tuple	ray_position(t_ray *ray, double t)
{
	return (vect_addition(ray->origin, vect_multiplication(ray->direction, t)));
}

t_hit	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_hit		hit;
	t_tuple	sphere_to_ray;
	double		t1;
	double		t2;
	double a, b, c, discriminant;
	sphere_to_ray = vect_subtraction(ray.origin, sphere.center);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(sphere_to_ray, ray.direction);
	c = dot_product(sphere_to_ray, sphere_to_ray) - sphere.radius
		* sphere.radius;
	discriminant = b * b - 4 * a * c;
	hit.hit = 0;
	if (discriminant >= 0)
	{
		t1 = (-b - sqrt(discriminant)) / (2 * a);
		t2 = (-b + sqrt(discriminant)) / (2 * a);
		printf(YEL"t1: %f"RESET, t1);
		printf(YEL"t2: %f\n"RESET, t2);
		if (t1 > 0 && t1 < t2)
		{
			printf(MAG"NO HIT\n"RESET);
			hit.t = t1;
		}
		else if (t2 > 0)
		{
			printf(YEL"NO HIT\n"RESET);
			hit.t = t2;
		}
		else
		{
			printf(RED"NO HIT\n"RESET);
			return (hit);
		}
		hit.hit = 1;
		hit.point = ray_position(&ray, hit.t);
		hit.normal = normalize_vect(vect_subtraction(hit.point, sphere.center));
		hit.material = sphere.material;
	}
	printf(GRN"Hit in intersect_sphere: %d\n"RESET, hit.hit);
	return (hit);
}

t_tuple	reflect(t_tuple incident, t_tuple normal)
{
	return (vect_subtraction(incident, vect_multiplication(normal, 2
				* dot_product(incident, normal))));
}

t_color	trace_ray(t_ray ray, t_scene *scene, int depth)
{
	t_hit	hit;
	t_color	color;
			t_ray reflected_ray;
	t_color	reflected_color;

	hit = intersect_scene(ray, scene);
	// printf(MAG"Hit in trace_ray: %d\n", hit.hit);
	// printf("hit point %f %f %f %f\n", hit.point.x, hit.point.y, hit.point.z, hit.point.w);
	if (hit.hit)
	{
		color = calculate_lighting(hit, scene, ray);
		if (depth > 0 && hit.material.reflective > 0)
		{
			reflected_ray.origin = hit.point;
			reflected_ray.direction = reflect(ray.direction, hit.normal);
			reflected_color = trace_ray(reflected_ray, scene, depth - 1);
			color = add_color(color, scale_color(reflected_color,
						hit.material.reflective));
		}
		printf("Color: %d, %d, %d", color.r, color.g, color.b);
		return (color);
	}
	return (scene->background_color);
}
