#include "minirt.h"

// int	main(int argc, char **argv)
// {
// 	static t_data	data;

// 	(void)argc;
// 	(void)argv;
// 	data.mlx_ptr = mlx_init();
// 	if (data.mlx_ptr == NULL)
// 		return (MLX_ERROR);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "miniRT");
// 	if (data.win_ptr == NULL)
// 	{
// 		free(data.mlx_ptr);
// 		return (MLX_ERROR);
// 	}
// 	// modif here?
// 	init_scene(&data.scene);
// 	// draw the initial scene
// 	if (render_frame(&data) == MLX_ERROR)
// 	{
// 		// error
// 		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
// 		free(data.mlx_ptr);
// 		return (MLX_ERROR);
// 	}
// 	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
// 	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
// 	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
// 		&data);
// 	mlx_loop(data.mlx_ptr);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	static t_data data;

	(void)argc;
	(void)argv;

	printf("Initializing MLX...\n");
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);

	printf("Creating window...\n");
	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "miniRT");
	if (data.win_ptr == NULL)
	{
		free(data.mlx_ptr);
		return (MLX_ERROR);
	}

	printf("Initializing scene...\n");
	init_scene(&data.scene);

	printf("Creating image...\n");
	data.img_ptr = mlx_new_image(data.mlx_ptr, W_WIDTH, W_HEIGHT);
	data.addr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel,
			&data.line_length, &data.endian);

	printf("Rendering frame...\n");
	if (render_frame(&data) == MLX_ERROR)
	{
		printf("Error rendering frame\n");
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		free(data.mlx_ptr);
		return (MLX_ERROR);
	}

	printf("Setting up hooks...\n");
	mlx_hook(data.win_ptr, 17, 1L << 17, handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);

	printf("Starting MLX loop...\n");
	mlx_loop(data.mlx_ptr);

	return (0);
}