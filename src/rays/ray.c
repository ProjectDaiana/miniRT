#include "minirt.h"

t_ray	 create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_tuple	position(t_ray ray, double t)
{
	return (tuple_add(ray.origin, tuple_multiply(ray.direction, t)));
}

t_color	ray_color(t_scene *scene, t_ray ray)
{
	t_intersections	xs;
	t_tuple			point;
	t_tuple			normal;
	t_tuple			eye;
	int				in_shadow;

	xs = intersect_world(scene, ray);
	if (xs.count > 0)
	{
		point = position(ray, xs.t[0]);
		//normal = normal_at(*(t_sphere *)xs.object[0], point);
		normal = normal_at_cylinder(*(t_cylinder *)xs.object[0], point);
		eye = tuple_negate(ray.direction);
		in_shadow = is_shadowed(scene, point, &scene->light);
		// return (lighting(((t_sphere *)xs.object[0])->material, scene->light,
		// 		point, eye, normal, in_shadow));
		return (lighting(((t_cylinder *)xs.object[0])->material, scene->light,
				point, eye, normal, in_shadow));
	}
	return (create_color(0, 0, 0));
}

// t_ray	ray_for_pixel(t_camera *camera, int px, int py)
// {
// 	double x = (px + 0.5) / W_WIDTH;
// 	double y = (py + 0.5) / W_HEIGHT;
// 	x = 2 * x - 1;
// 	y = 1 - 2 * y;
// 	x *= camera->half_width;
// 	y *= camera->half_height;

// 	t_tuple world_point = tuple_add(camera->position,
// 			tuple_add(tuple_multiply(camera->right, x),
// 				tuple_multiply(camera->up, y)));
// 	t_tuple pixel = tuple_subtract(world_point, camera->position);
// 	t_tuple direction = tuple_normalize(pixel);

// 	return (create_ray(camera->position, direction));
// }



t_ray	ray_for_pixel(t_camera *camera, int px, int py)
{
	double		x;
	double		y;
	t_matrix	inverse_transform;
	t_tuple		world_pixel;
	t_tuple		origin;
	t_tuple		direction;

	x = (px + 0.5) / W_WIDTH;
	y = (py + 0.5) / W_HEIGHT;
	x = 2 * x - 1;
	y = 1 - 2 * y;
	x *= camera->half_width;
	y *= camera->half_height;
	t_tuple pixel = create_point(x, y, -1); //
	inverse_transform = inverse_matrix(&camera->transform);
	print_matrix(inverse_transform, "Inverse Transform", 4);
	world_pixel = matrix_multiply_tuple(inverse_transform, pixel);
	origin = matrix_multiply_tuple(inverse_transform, create_point(0, 0, 0));
	direction = tuple_normalize(tuple_subtract(world_pixel, origin));
	return (create_ray(origin, direction));
}
