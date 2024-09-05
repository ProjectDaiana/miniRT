#include "minirt.h"

int	render_frame(t_data *data)
{
	t_ray	ray;
	t_color	color;
	t_hit	hit;
	int		checker;

	double u, v;
	int x, y;
	// Clear the image buffer
	ft_memset(data->addr, 0, W_WIDTH * W_HEIGHT * (data->bits_per_pixel / 8));
	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			u = (double)x / (W_WIDTH - 1);
			v = (double)(W_HEIGHT - 1 - y) / (W_HEIGHT - 1);
			ray = create_ray(u, v, &data->scene.camera);
			hit = intersect_scene(ray, &data->scene);
			if (hit.hit)
			{
				color = calculate_lighting(hit, &data->scene, ray);
			}
			else
			{
				checker = (int)(floor(u * 10) + floor(v * 10)) % 2;
				color = checker ? create_color(200, 200,
						200) : create_color(100, 100, 100);
			}
			my_mlx_pixel_put(data, x, y, rgb_to_int(color));
			x++;
		}
		y++;
	}
	// Put the image to the window
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

// t_hit	intersect_sphere(t_ray ray, t_sphere sphere)
// {
// 	t_hit		hit;
// 	t_vector	oc;
// 	t_vector	scaled_direction;
// 	t_vector	scaled_oc;

// 	double a, b, c, discriminant, t;
// 	double scale_x, scale_y, scale_z;
// 	hit.hit = 0;
// 	hit.t = 0;
// 	hit.point = (t_vector){0, 0, 0};
// 	hit.normal = (t_vector){0, 0, 0};
// 	oc = vect_subtraction(ray.origin, sphere.center);
// 	scale_x = sphere.radius;
// 	scale_y = sphere.radius;
// 	scale_z = sphere.radius;
// 	scaled_direction.x = ray.direction.x / scale_x;
// 	scaled_direction.y = ray.direction.y / scale_y;
// 	scaled_direction.z = ray.direction.z / scale_z;
// 	scaled_oc.x = oc.x / scale_x;
// 	scaled_oc.y = oc.y / scale_y;
// 	scaled_oc.z = oc.z / scale_z;
// 	a = dot_product(scaled_direction, scaled_direction);
// 	b = 2.0 * dot_product(scaled_oc, scaled_direction);
// 	c = dot_product(scaled_oc, scaled_oc) - 1.0;
// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 		return (hit);
// 	t = (-b - sqrt(discriminant)) / (2.0 * a);
// 	if (t > 0)
// 	{
// 		hit.hit = 1;
// 		hit.t = t;
// 		hit.point = vect_addition(ray.origin, vect_multiplication(ray.direction,
// 					t));
// 		hit.normal = vect_normalize((t_vector){(hit.point.x - sphere.center.x)
// 				/ (scale_x * scale_x), (hit.point.y - sphere.center.y)
// 				/ (scale_y * scale_y), (hit.point.z - sphere.center.z)
// 				/ (scale_z * scale_z)});
// 	}
// 	return (hit);
// }
t_hit	intersect_scene(t_ray ray, t_scene *scene)
{
	t_hit	closest_hit;
	t_hit	current_hit;
	int		i;

	closest_hit.hit = 0;
	closest_hit.t = INFINITY;
	i = 0;
	while (i < scene->sphere_count)
	{
		current_hit = intersect_sphere(ray, scene->spheres[i]);
		if (current_hit.hit && current_hit.t < closest_hit.t)
		{
			closest_hit = current_hit;
		}
		i++;
	}
	return (closest_hit);
}
