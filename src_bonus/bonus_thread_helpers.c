/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_thread_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:07:47 by tasha             #+#    #+#             */
/*   Updated: 2024/12/29 20:53:24 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_thread_data(t_thread_data *data, int *pixels_done,
		int *total_pixels)
{
	if (!data || !pixels_done || !total_pixels)
		return ;
	*pixels_done = 0;
	*total_pixels = (data->end_y - data->start_y) * W_WIDTH;
}

// static void	print_progress(int thread_id, int pixels_done, int total_pixels)
// {
// 	if (pixels_done % 1000 == 0)
// 		printf("Thread %d: %.1f%% complete\n", thread_id,
// 			(float)pixels_done / total_pixels * 100);
// }

// static void	render_row(t_thread_data *data, int y, int *pixels_done,
//		int total_pixels)

void	render_row(t_thread_data *data, int y, int *pixels_done)
{
	int		x;
	t_tuple	pixel;

	x = 0;
	while (x < W_WIDTH)
	{
		pixel = (t_tuple){x, y, 0, 1};
		render_pixel(data->scene, data->camera, data->canvas, pixel);
		(*pixels_done)++;
		x++;
	}
}

void	*render_pixels(void *arg)
{
	t_thread_data	*data;
	int				pixels_done;
	int				total_pixels;
	int				y;

	if (!arg)
		return (NULL);
	data = (t_thread_data *)arg;
	if (!data->scene || !data->camera || !data->canvas || data->start_y < 0
		|| data->end_y > W_HEIGHT)
		return (NULL);
	init_thread_data(data, &pixels_done, &total_pixels);
	y = data->start_y;
	while (y < data->end_y)
	{
		render_row(data, y, &pixels_done);
		y++;
	}
	return (NULL);
}
