/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/23 20:17:51 by tasha            ###   ########.fr       */
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

	if (!arg)
		return (NULL);
	data = (t_thread_data *)arg;
	
	if (!data->scene || !data->camera || !data->canvas 
		|| data->start_y < 0 || data->end_y > W_HEIGHT)
		return (NULL);
		
	y = data->start_y;
	while (y < data->end_y)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			t_tuple pixel = {x, y, 0, 1};
			render_pixel(data->scene, data->camera, data->canvas, pixel);
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
				pthread_join(threads[i], NULL);
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
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_attr_destroy(&attr);
}

int	render(t_data *data)
{
	t_canvas		canvas;
	t_camera		camera;
	t_tuple			up;
	t_matrix		transform;
	pthread_attr_t	attr;

	canvas = create_canvas(W_WIDTH, W_HEIGHT);
	camera = create_camera(W_WIDTH, W_HEIGHT, data->scene.camera.fov * M_PI
			/ 180.0);
	up = create_vector(0, 1, 0);
	transform = look_at(data->scene.camera.position,
			tuple_add(data->scene.camera.position,
				data->scene.camera.orientation), up);
	if (!transform.m)
	{
		free_canvas(&canvas);
		return (1);
	}

	camera.transform = transform;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	render_threads(data, &camera, &canvas);
	pthread_attr_destroy(&attr);

	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	if (!data->img.img)
	{
		free_canvas(&canvas);
		free_mtrx(&transform);
		return (1);
	}

	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	copy_to_image(data, &canvas);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	
	free_canvas(&canvas);
	free_mtrx(&transform);
	return (0);
}
