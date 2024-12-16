// #include "minirt.h"

// void	init(t_data *data, t_vector *vector)
// {
// 	data->mlx_ptr = NULL;
// 	data->win_ptr = NULL;
// 	vector->x = 1.0;
// 	vector->y = 2.0;
// 	vector->z = 3.0;
// 	vector->magnitude = 0.0;
// }

// int	render(t_data *data)
// {
// 	t_color	color1;
// 	t_color	color2;
// 	int		x;
// 	int		y;

// 	if (data->win_ptr != NULL)
// 	{
// 		// Clear window (optional, may not be necessary every frame)
// 		draw_clock(data);
// 		color1.r = 100;
// 		color1.g = 0;
// 		color1.b = 50;
// 		color2.r = 2;
// 		color2.g = 0;
// 		color2.b = 3;
// 		x = (int)(data->tuple->x * SCALE) + W_WIDTH / 2;
// 		y = (int)(data->tuple->y * SCALE) + W_HEIGHT / 2;
// 		if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
// 		{
// 			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, add_color(&color1,
// 					&color2));
// 		}
// 	}
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
// 	static t_data data;
// 	t_vector vector;

// 	init(&data, &vector);

// 	///////// MATRIX CREATION TESTS //////////////////////////

// 	double identity_matrix[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0},
// 		{0, 0, 0, 1}};
// 	t_matrix identity = create_matrix(4);
// 	assign_matrix(&identity, identity_matrix);
// 	// print_matrix(identity, "Identity Matrix", 4);

// 	//////// MINILIBX /////////////////////////////
// 	data.mlx_ptr = mlx_init();
// 	if (data.mlx_ptr == NULL)
// 		return (MLX_ERROR);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "miniRT");
// 	if (data.win_ptr == NULL)
// 	{
// 		free(data.mlx_ptr);
// 		return (MLX_ERROR);
// 	}
// 	//// Render the scene
// 	// CLOCK EXERCISE
// 	draw_clock(&data);

// 	// TRANSFORM TESTS
// 	t_tuple origin = {1, 2, 3, 1};
// 	t_tuple dir = {0, 1, 0, 0};
// 	t_ray ray = {origin, dir};
// 	t_matrix scale = scaling(2, 3, 4);
// 	transform(&ray, &scale);

// 	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
// 	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
// 		&data);
// 	mlx_loop(data.mlx_ptr);
// 	return (0);
// }

#include "minirt.h"

// ok
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
	if (!data.scene.spheres)
	{
		printf("Error: Scene initialization failed\n");
		return (1);
	}
	render(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
		&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
