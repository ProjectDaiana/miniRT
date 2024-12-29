/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_render_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:00:59 by tasha             #+#    #+#             */
/*   Updated: 2024/12/29 19:46:22 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_thread_attr(pthread_attr_t *attr)
{
	pthread_attr_init(attr);
	pthread_attr_setdetachstate(attr, PTHREAD_CREATE_JOINABLE);
}

static void	init_thread_data_array(t_thread_data *thread_data, t_data *data,
		t_camera *camera, t_canvas *canvas)
{
	int	i;
	int	start_y;
	int	end_y;

	memset(thread_data, 0, sizeof(t_thread_data) * THREADS);
	start_y = 0;
	end_y = W_HEIGHT / THREADS;
	i = 0;
	while (i < THREADS)
	{
		thread_data[i].canvas = canvas;
		thread_data[i].scene = &data->scene;
		thread_data[i].camera = camera;
		thread_data[i].start_y = start_y;
		thread_data[i].end_y = end_y;
		start_y = end_y;
		end_y += W_HEIGHT / THREADS;
		i++;
	}
}

static void	cleanup_threads(pthread_t *threads, int count, void **status)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(threads[i], status);
		if (*status)
			free(*status);
		i++;
	}
}

void	render_threads(t_data *data, t_camera *camera, t_canvas *canvas)
{
	pthread_t		threads[THREADS];
	t_thread_data	thread_data[THREADS];
	pthread_attr_t	attr;
	void			*status;
	int				i;

	init_thread_attr(&attr);
	init_thread_data_array(thread_data, data, camera, canvas);
	i = 0;
	printf("\033[0;33mRendering with %d threads\033[0m\n", THREADS);
	while (i < THREADS)
	{
		if (pthread_create(&threads[i], &attr, render_pixels,
				&thread_data[i]) != 0)
		{
			cleanup_threads(threads, i, &status);
			pthread_attr_destroy(&attr);
			return ;
		}
		i++;
	}
	cleanup_threads(threads, THREADS, &status);
	pthread_attr_destroy(&attr);
}
