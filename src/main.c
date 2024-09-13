#include "minirt.h"

void	init(t_data *data, t_vector *vector)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	vector->x = 1.0;
	vector->y = 2.0;
	vector->z = 3.0;
}

// int	main(int argc, char **argv)
// {
// 	t_data	data;
// 	t_scene	scene;

// 	if (argc != 2)
// 	{
// 		printf("Usage: %s <scene.rt>\n", argv[0]);
// 		return (1);
// 	}
// 	ft_memset(&scene, 0, sizeof(t_scene));
// 	if (!parse_rt_file(argv[1], &scene))
// 	{
// 		printf("Error: Failed to parse .rt file\n");
// 		return (1);
// 	}
// 	printf("Parsed scene:\n");
// 	printf("Sphere count: %d\n", scene.sphere_count);
// 	for (int i = 0; i < scene.sphere_count; i++)
// 	{
// 		printf("Sphere %d: center(%f, %f, %f), radius: %f\n", i,
// 			scene.spheres[i].center.x, scene.spheres[i].center.y,
// 			scene.spheres[i].center.z, scene.spheres[i].radius);
// 	}
// 	data.mlx_ptr = mlx_init();
// 	if (data.mlx_ptr == NULL)
// 		return (MLX_ERROR);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "miniRT");
// 	if (data.win_ptr == NULL)
// 	{
// 		free(data.mlx_ptr);
// 		return (MLX_ERROR);
// 	}
// 	data.scene = scene;
// 	data.img_ptr = mlx_new_image(data.mlx_ptr, W_WIDTH, W_HEIGHT);
// 	data.addr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel,
// 			&data.line_length, &data.endian);
// 	printf("Rendering frame...\n");
// 	render_img(&data);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_data data;
	t_scene scene;

	if (argc != 2)
	{
		printf("Usage: %s <scene.rt>\n", argv[0]);
		return (1);
	}

	ft_memset(&scene, 0, sizeof(t_scene));
	if (!parse_rt_file(argv[1], &scene))
	{
		printf("Error: Failed to parse .rt file\n");
		return (1);
	}

	printf("Parsed scene:\n");
	print_scene_info(&scene);

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	{
		printf("Error: mlx_init failed\n");
		return (MLX_ERROR);
	}

	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "miniRT");
	if (data.win_ptr == NULL)
	{
		printf("Error: mlx_new_window failed\n");
		free(data.mlx_ptr);
		return (MLX_ERROR);
	}

	data.scene = scene;
	data.img_ptr = mlx_new_image(data.mlx_ptr, W_WIDTH, W_HEIGHT);
	data.addr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel,
			&data.line_length, &data.endian);

	printf("Rendering frame...\n");
	if (render_img(&data) == MLX_ERROR)
	{
		printf("Error: render_img failed\n");
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		free(data.mlx_ptr);
		return (MLX_ERROR);
	}

	mlx_loop(data.mlx_ptr);

	// This point is reached only if mlx_loop exits
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);

	return (0);
}