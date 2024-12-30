/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:26:58 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 12:31:31 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	init_program(t_data *data, t_vector *vector, char *scene_file)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	vector->x = 1.0;
	vector->y = 2.0;
	vector->z = 3.0;
	vector->magnitude = 0.0;
	if (init_mlx(data) == MLX_ERROR)
		return (MLX_ERROR);
	parse_scene(scene_file, &data->scene);
	return (0);
}

static int	setup_and_render(t_data *data)
{
	render(data);
	setup_hooks(data);
	mlx_loop(data->mlx_ptr);
	free_scene(&data->scene);
	close_window(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_vector	vector;

	if (argc != 2)
	{
		printf("Usage: %s <scene_file.rt>\n", argv[0]);
		return (1);
	}
	if (init_program(&data, &vector, argv[1]))
		return (1);
	return (setup_and_render(&data));
}
