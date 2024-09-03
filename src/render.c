#include "minirt.h"

// int	render_frame(t_data *data)
// {
// 	Ray		ray;
// 	t_color	color;
// 	t_color	accumulated_color;
// 	double	u;
// 	double	v;

// 	int samples = 2; // Reduce samples for faster rendering during testing
// 	for (int y = 0; y < W_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < W_WIDTH; x++)
// 		{
// 			accumulated_color = {0, 0, 0};
// 			for (int s = 0; s < samples; s++)
// 			{
// 				u = ((double)x + ((double)rand() / RAND_MAX)) / W_WIDTH;
// 				v = ((double)y + ((double)rand() / RAND_MAX)) / W_HEIGHT;
// 				ray = create_ray(u, v);
// 				color = trace_ray(ray, &data->scene);
// 				accumulated_color = add_color(accumulated_color, color);
// 			}
// 			color = multiply_color_by_scalar(accumulated_color, 1.0 / samples);
// 			// Ensure color values are within valid range
// 			color.r = fmin(fmax(color.r, 0), 255);
// 			color.g = fmin(fmax(color.g, 0), 255);
// 			color.b = fmin(fmax(color.b, 0), 255);
// 			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y,
// 				(color.r << 16) | (color.g << 8) | color.b);
// 		}
// 	}
// 	return (0);
// }

int	render_frame(t_data *data)
{
	Ray		ray;
	t_color	color;
	t_color	accumulated_color;
	double	u;
	double	v;

	int samples = 2; // Reduce samples for faster rendering during testing
	for (int y = 0; y < W_HEIGHT; y++)
	{
		for (int x = 0; x < W_WIDTH; x++)
		{
			accumulated_color.r = 0;
			accumulated_color.g = 0;
			accumulated_color.b = 0;
			for (int s = 0; s < samples; s++)
			{
				u = ((double)x + ((double)rand() / RAND_MAX)) / W_WIDTH;
				v = ((double)y + ((double)rand() / RAND_MAX)) / W_HEIGHT;
				ray = create_ray(u, v);
				color = trace_ray(ray, &data->scene);
				accumulated_color = add_color(accumulated_color, color);
			}
			color = multiply_color_by_scalar(accumulated_color, 1.0 / samples);
			// Ensure color values are within valid range
			color.r = fmin(fmax(color.r, 0), 255);
			color.g = fmin(fmax(color.g, 0), 255);
			color.b = fmin(fmax(color.b, 0), 255);
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y,
				(color.r << 16) | (color.g << 8) | color.b);
		}
	}
	return (0);
}

t_hit	intersect_sphere(Ray ray, t_sphere sphere)
{
	t_hit		hit;
	t_vector	oc;
	t_vector	scaled_direction;
	t_vector	scaled_oc;

	double a, b, c, discriminant, t;
	double scale_x, scale_y, scale_z;
	hit.hit = 0;
	hit.t = 0;
	hit.point = (t_vector){0, 0, 0};
	hit.normal = (t_vector){0, 0, 0};
	oc = vect_subtraction(ray.origin, sphere.center);
	scale_x = sphere.radius;
	scale_y = sphere.radius;
	scale_z = sphere.radius;
	scaled_direction.x = ray.direction.x / scale_x;
	scaled_direction.y = ray.direction.y / scale_y;
	scaled_direction.z = ray.direction.z / scale_z;
	scaled_oc.x = oc.x / scale_x;
	scaled_oc.y = oc.y / scale_y;
	scaled_oc.z = oc.z / scale_z;
	a = dot_product(scaled_direction, scaled_direction);
	b = 2.0 * dot_product(scaled_oc, scaled_direction);
	c = dot_product(scaled_oc, scaled_oc) - 1.0;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t > 0)
	{
		hit.hit = 1;
		hit.t = t;
		hit.point = vect_addition(ray.origin, vect_multiplication(ray.direction,
					t));
		hit.normal = vect_normalize((t_vector){(hit.point.x - sphere.center.x)
				/ (scale_x * scale_x), (hit.point.y - sphere.center.y)
				/ (scale_y * scale_y), (hit.point.z - sphere.center.z)
				/ (scale_z * scale_z)});
	}
	return (hit);
}
// void render(t_scene *scene)
// {
// 	int x, y;
// 	Ray ray;
// 	t_color color;

// 	for (y = 0; y < W_HEIGHT; y++) {
// 		for (x = 0; x < W_WIDTH; x++) {
// 			ray = create_ray((double)x / W_WIDTH, (double)y / W_HEIGHT);
// 			color = trace_ray(ray, scene);
// 			put_pixel(&scene->img, x, y, rgb_to_int(color));
// 		}
// 	}
// 	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
// }

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

