#include "minirt.h"

// int render(t_data *data)
// {
//     if (data->win_ptr != NULL)
//     {
//         // Clear window
//         //mlx_clear_window(data->mlx_ptr, data->win_ptr);
// 		draw_clock(data);

// 		t_color color1 = {100, 0, 50};
// 		t_color color2 = {2, 0, 3};
// 		int x = (int)(data->tuple->x * SCALE) + W_WIDTH / 2;
//         int y = (int)(data->tuple->y * SCALE) + W_HEIGHT / 2;
// 		if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
// 		{
// 			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, add_color(&color1, &color2));

// 		}
//     }
//     return (0);
// }


int render_img(t_data *data)
{
	if (render_frame(data) == MLX_ERROR)
	{
		printf("Error rendering frame\n");
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->mlx_ptr);
		return (MLX_ERROR);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	mlx_hook(data->win_ptr, 17, 1L << 17, close_window, &data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

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
			ray = create_ray(u, v);
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