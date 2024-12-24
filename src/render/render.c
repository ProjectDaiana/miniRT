/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/24 01:02:59 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <pthread.h>

static void	render_pixel(t_scene *scene, t_camera *camera, t_canvas *canvas,
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

// No-threaded version of render_pixels
// static void	render_pixels(t_scene *scene, t_camera *camera,
//		t_canvas *canvas)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < W_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < W_WIDTH)
// 		{
// 			render_pixel(scene, camera, canvas, (t_tuple){x, y, 0, 1});
// 			x++;
// 		}
// 		y++;
// 	}
// }

// int	render(t_data *data)
// {
// 	t_canvas	canvas;
// 	t_camera	camera;
// 	t_tuple		up;
// 	t_matrix	transform;

// 	canvas = create_canvas(W_WIDTH, W_HEIGHT);
// 	camera = create_camera(W_WIDTH, W_HEIGHT, data->scene.camera.fov * M_PI
// 			/ 180.0);
// 	up = create_vector(0, 1, 0);
// 	transform = look_at(data->scene.camera.position,
// 			tuple_add(data->scene.camera.position,
// 				data->scene.camera.orientation), up);
// 	if (!transform.m)
// 		return (1);
// 	camera.transform = transform;
// 	render_pixels(&data->scene, &camera, &canvas);
// 	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
// 	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
// 			&data->img.line_length, &data->img.endian);
// 	copy_to_image(data, &canvas);
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
// 	free_canvas(&canvas);
// 	return (0);
// }

//	Threaded version of render_pixels
static void	*render_pixels(void *arg)
{
	t_thread_data	*data;
	int				x;
	int				y;
	int				total_pixels;
	int				pixels_done;
	t_tuple			pixel;

	pixels_done = 0;
	if (!arg)
		return (NULL);
	data = (t_thread_data *)arg;
	if (!data->scene || !data->camera || !data->canvas || data->start_y < 0
		|| data->end_y > W_HEIGHT)
		return (NULL);
	total_pixels = (data->end_y - data->start_y) * W_WIDTH;
	y = data->start_y;
	while (y < data->end_y)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			pixel.x = x;
			pixel.y = y;
			pixel.z = 0;
			pixel.w = 1;
			render_pixel(data->scene, data->camera, data->canvas, pixel);
			pixels_done++;
			if (pixels_done % 1000 == 0)
				printf("Thread %d: %.1f%% complete\n", (int)(data->start_y
						/ (W_HEIGHT / THREADS)), (float)pixels_done
					/ total_pixels * 100);
			x++;
		}
		y++;
	}
	return (NULL);
}

void	render_threads(t_data *data, t_camera *camera, t_canvas *canvas)
{
	pthread_t		threads[THREADS];
	t_thread_data	thread_data[THREADS];
	pthread_attr_t	attr;
	int				i;
	int				start_y;
	int				end_y;
	void			*status;

	memset(thread_data, 0, sizeof(t_thread_data) * THREADS);
	start_y = 0;
	end_y = W_HEIGHT / THREADS;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	i = 0;
	while (i < THREADS)
	{
		thread_data[i].canvas = canvas;
		thread_data[i].scene = &data->scene;
		thread_data[i].camera = camera;
		thread_data[i].start_y = start_y;
		thread_data[i].end_y = end_y;
		if (pthread_create(&threads[i], &attr, render_pixels,
				&thread_data[i]) != 0)
		{
			while (--i >= 0)
			{
				pthread_join(threads[i], &status);
				if (status)
					free(status);
			}
			pthread_attr_destroy(&attr);
			return ;
		}
		start_y = end_y;
		end_y += W_HEIGHT / THREADS;
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i], &status);
		if (status)
			free(status);
		i++;
	}
	pthread_attr_destroy(&attr);
}

int	render(t_data *data)
{
	t_canvas	canvas;
	t_camera	camera;
	t_tuple		up;
	t_matrix	transform;

	canvas = create_canvas(W_WIDTH, W_HEIGHT);
	camera = create_camera(W_WIDTH, W_HEIGHT, data->scene.camera.fov * M_PI / 180.0);
	up = create_vector(0, 1, 0);
	
	if (data->img.img)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.img);
		data->img.img = NULL;
	}
	
	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	if (!data->img.img)
	{
		free_canvas(&canvas);
		free_mtrx(&camera.transform);
		return (1);
	}
	
	if (camera.transform.m)
		free_mtrx(&camera.transform);
		
	transform = look_at(data->scene.camera.position,
			tuple_add(data->scene.camera.position,
				data->scene.camera.orientation), up);
	if (!transform.m)
	{
		free_canvas(&canvas);
		free_mtrx(&camera.transform);
		return (1);
	}
	camera.transform = transform;
	render_threads(data, &camera, &canvas);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	copy_to_image(data, &canvas);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	free_canvas(&canvas);
	free_mtrx(&camera.transform);
	return (0);
}
