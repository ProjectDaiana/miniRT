#include "minirt.h"

// int	render(t_data *data)
// {
// 	t_canvas	canvas;
// 	t_scene		*scene;
// 	double		aspect_ratio;
// 	t_ray		ray;
// 	t_color		color;
// 	int			color_int;
// 	double		viewport_height;
// 	double		viewport_width;
// 	double		focal_length;
// 	t_tuple		origin;
// 	t_tuple		horizontal;
// 	t_tuple		vertical;
// 	t_tuple		lower_left_corner;
// 	double		u;
// 	double		v;

// 	printf("Starting render...\n");
// 	canvas = create_canvas(W_WIDTH, W_HEIGHT);
// 	scene = &data->scene;
// 	// camera setup
// 	aspect_ratio = (double)W_WIDTH / W_HEIGHT;
// 	viewport_height = 2.0;
// 	viewport_width = aspect_ratio * viewport_height;
// 	focal_length = 1.0;
// 	origin = scene->camera.position;
// 	horizontal = create_vector(viewport_width, 0, 0);
// 	vertical = create_vector(0, viewport_height, 0);
// 	lower_left_corner = tuple_subtract(tuple_subtract(tuple_subtract(origin,
// 					tuple_divide(horizontal, 2)), tuple_divide(vertical, 2)),
// 			create_vector(0, 0, focal_length));
// 	for (int y = 0; y < W_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < W_WIDTH; x++)
// 		{
// 			u = (double)x / (W_WIDTH - 1);
// 			v = (double)(W_HEIGHT - 1 - y) / (W_HEIGHT - 1);
// 			ray.origin = origin;
// 			ray.direction = tuple_normalize(tuple_subtract(tuple_add(tuple_add(lower_left_corner,
// 								tuple_multiply(horizontal, u)),
// 							tuple_multiply(vertical, v)), origin));
// 			color = ray_color(scene, ray);
// 			write_pixel(&canvas, x, y, color);
// 		}
// 	}
// 	printf("Render complete. Converting to MLX image...\n");
// 	// Convert canvas to MLX image
// 	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
// 	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
// 			&data->img.line_length, &data->img.endian);
// 	for (int y = 0; y < W_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < W_WIDTH; x++)
// 		{
// 			color = pixel_at(&canvas, x, y);
// 			color_int = rgb_to_int(color);
// 			my_mlx_pixel_put(&data->img, x, y, color_int);
// 		}
// 	}
// 	printf("Putting image to window...\n");
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
// 	free_canvas(&canvas);
// 	return (0);
// }

int	render(t_data *data)
{
	t_canvas canvas;
	t_scene *scene;
	t_ray ray;
	t_color color;
	int color_int;

	printf("Starting render...\n");
	canvas = create_canvas(W_WIDTH, W_HEIGHT);
	scene = &data->scene;

	// Create view transform
	t_matrix translation = m_translation(-scene->camera.position.x,
			-scene->camera.position.y, -scene->camera.position.z);
	t_matrix rotation = rotation_y(-atan2(scene->camera.orientation.x,
				scene->camera.orientation.z));
	t_matrix view_transform = matrix_multiply(rotation, translation);
	t_matrix inv_view_transform = inverse_matrix(&view_transform);

	for (int y = 0; y < W_HEIGHT; y++)
	{
		for (int x = 0; x < W_WIDTH; x++)
		{
			double u = (double)x / (W_WIDTH - 1);
			double v = (double)(W_HEIGHT - 1 - y) / (W_HEIGHT - 1);

			// Calculate ray direction
			t_tuple direction = create_vector((2 * u - 1)
					* tan(scene->camera.fov / 2) * W_WIDTH / W_HEIGHT, (1 - 2
						* v) * tan(scene->camera.fov / 2), -1);
			direction = tuple_normalize(direction);

			// Transform ray
			t_tuple transformed_origin = matrix_multiply_tuple(inv_view_transform,
					scene->camera.position);
			t_tuple transformed_direction = matrix_multiply_tuple(inv_view_transform,
					direction);
			transformed_direction = tuple_normalize(transformed_direction);

			ray = create_ray(transformed_origin, transformed_direction);
			color = ray_color(scene, ray);
			write_pixel(&canvas, x, y, color);
		}
	}

	printf("Render complete. Converting to MLX image...\n");
	// Convert canvas to MLX image
	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	for (int y = 0; y < W_HEIGHT; y++)
	{
		for (int x = 0; x < W_WIDTH; x++)
		{
			color = pixel_at(&canvas, x, y);
			color_int = rgb_to_int(color);
			my_mlx_pixel_put(&data->img, x, y, color_int);
		}
	}
	printf("Putting image to window...\n");
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	free_canvas(&canvas);
	return (0);

}