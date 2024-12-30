/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:55:21 by darotche          #+#    #+#             */
/*   Updated: 2024/12/30 13:20:41 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_pixel(t_scene *scene, t_camera *camera, t_canvas *canvas,
		t_tuple pixel)
{
	t_ray	ray;
	t_color	color;

	ray = ray_for_pixel(camera, pixel.x, pixel.y);
	color = ray_color(scene, ray);
	write_pixel(canvas, pixel.x, pixel.y, color);
}

static void	copy_to_image(t_data *data, t_canvas *canvas)
{
	int		x;
	int		y;
	t_color	color;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			color = pixel_at(canvas, x, y);
			my_mlx_pixel_put(&data->img, x, y, rgb_to_int(color));
			x++;
		}
		y++;
	}
}

static void	render_pixels_no_threads(t_scene *scene, t_camera *camera,
	t_canvas *canvas)
{
	int		x;
	int		y;
	t_tuple	pixel;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			pixel = (t_tuple){x, y, 0, 1};
			render_pixel(scene, camera, canvas, pixel);
			x++;
		}
		y++;
	}
}

static int	setup_camera_and_canvas(t_data *data, t_canvas *canvas,
	t_camera *camera)
{
	t_tuple		up;
	t_matrix	transform;

	*canvas = create_canvas(W_WIDTH, W_HEIGHT);
	*camera = create_camera(W_WIDTH, W_HEIGHT,
			data->scene.camera.fov * M_PI / 180.0);
	up = create_vector(0, 1, 0);
	transform = look_at(data->scene.camera.position,
			tuple_add(data->scene.camera.position,
				data->scene.camera.orientation), up);
	if (!transform.m)
	{
		cleanup_camera(camera);
		free_canvas(canvas);
		return (1);
	}
	cleanup_camera(camera);
	camera->transform = transform;
	return (0);
}

int	render(t_data *data)
{
	t_canvas	canvas;
	t_camera	camera;

	if (setup_camera_and_canvas(data, &canvas, &camera))
		return (1);
	render_pixels_no_threads(&data->scene, &camera, &canvas);
	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	copy_to_image(data, &canvas);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	free_canvas(&canvas);
	cleanup_camera(&camera);
	return (0);
}
