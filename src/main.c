/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:26:58 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 19:57:15 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init(t_data *data, t_vector *vector)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	vector->x = 1.0;
	vector->y = 2.0;
	vector->z = 3.0;
	vector->magnitude = 0.0;
}

static int	init_scene(t_data *data, char *scene_file)
{
	printf("Parsing scene...\n");
	parse_scene(scene_file, &(data->scene));
	printf("Scene parsed\n");
	if (!data->scene.spheres)
	{
		printf("Error: Scene initialization failed\n");
		return (1);
	}
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
	init(&data, &vector);
	if (init_mlx(&data) == MLX_ERROR)
		return (MLX_ERROR);
	if (init_scene(&data, argv[1]))
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}
	render(&data);
	setup_hooks(&data);
	mlx_loop(data.mlx_ptr);
	
	// Cleanup (this will run after mlx_loop ends)
	free_scene(&data.scene);
	if (data.img.img)
		mlx_destroy_image(data.mlx_ptr, data.img.img);
	if (data.win_ptr)
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	if (data.mlx_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
	}
	return (0);
}
