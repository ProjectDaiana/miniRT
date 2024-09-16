#include "minirt.h"

void	init(t_data *data, t_vector *vector)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	vector->x = 1.0;
	vector->y = 2.0;
	vector->z = 3.0;
	vector->magnitude = 0.0;
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
	printf("Initializing data...\n");
	init(&data, &vector);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "miniRT");
	if (data.win_ptr == NULL)
	{
		free(data.mlx_ptr);
		return (MLX_ERROR);
	}
	data.img.img = mlx_new_image(data.mlx_ptr, W_WIDTH, W_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel,
			&data.img.line_length, &data.img.endian);
	// Parse the scene and render
	printf("Parsing scene...\n");
	parse_scene(argv[1], &(data.scene));
	printf("Scene parsed\n");
	render(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
		&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
