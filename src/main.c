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
		return (1);
	render(&data);
	setup_hooks(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
