#include "minirt.h"

// int	render_img(t_data *data)
// {
// 	if (render_frame(data) == MLX_ERROR)
// 	{
// 		printf("Error rendering frame\n");
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		free(data->mlx_ptr);
// 		return (MLX_ERROR);
// 	}
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
// 	mlx_hook(data->win_ptr, 17, 1L << 17, handle_keypress, &data);
// 	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
// 	mlx_loop(data->mlx_ptr);
// 	return (0);
// }

int	render_img(t_data *data)
{
	if (render_frame(data) == MLX_ERROR)
	{
		printf("Error rendering frame\n");
		close_window(data);
		return (MLX_ERROR);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	mlx_hook(data->win_ptr, 17, 1L << 17, close_window, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, handle_keyrelease,
		data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

// int	render_frame(t_data *data)
// {
// 	t_ray	ray;
// 	t_color	color;
// 	t_hit	hit;
// 	int		checker;

// 	double u, v;
// 	int x, y;
// 	// Clear the image buffer
// 	ft_memset(data->addr, 0, W_WIDTH * W_HEIGHT * (data->bits_per_pixel / 8));
// 	y = 0;
// 	while (y < W_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < W_WIDTH)
// 		{
// 			u = (double)x / (W_WIDTH - 1);
// 			v = (double)(W_HEIGHT - 1 - y) / (W_HEIGHT - 1);
// 			ray = create_ray(u, v);
// 			hit = intersect_scene(ray, &data->scene);
// 			if (hit.hit)
// 			{
// 				color = calculate_lighting(hit, &data->scene, ray);
// 			}
// 			else
// 			{
// 				checker = (int)(floor(u * 10) + floor(v * 10)) % 2;
// 				color = checker ? create_color(200, 200,
// 						200) : create_color(100, 100, 100);
// 			}
// 			my_mlx_pixel_put(data, x, y, rgb_to_int(color));
// 			x++;
// 		}
// 		y++;
// 	}
// 	// Put the image to the window
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
// 	return (0);
// }

int	render_frame(t_data *data)
{
	t_ray	ray;
	t_color	color;

	int x, y;
	if (data->scene.sphere_count == 0)
	{
		printf("No spheres to render. Filling screen with black.\n");
		// Fill screen with black
		for (int y = 0; y < W_HEIGHT; y++)
		{
			for (int x = 0; x < W_WIDTH; x++)
			{
				my_mlx_pixel_put(data, x, y, 0x000000);
			}
		}
		return (0);
	}
	for (y = 0; y < W_HEIGHT; y++)
	{
		for (x = 0; x < W_WIDTH; x++)
		{
			ray = create_camera_ray(data->scene.camera, x, y);
			color = trace_ray(ray, &data->scene, MAX_REFLECTION_DEPTH);
			my_mlx_pixel_put(data, x, y, rgb_to_int(color));
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}
