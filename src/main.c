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

	// TESTING
	test_truncated_cylinders();

	// t_ray ray = create_ray(create_point(1, 2, 3), create_vector(0, 1, 0));
	// t_matrix m = m_translation(3, 4, 5);
	// t_ray r2 = transform_ray(ray, m);
	// printf(BLU"r2.origin.x: %f %f %f \n"RESET, r2.origin.x, r2.origin.y, r2.origin.z);
	// printf(BLU"r2.direction.y: %f %f %f \n"RESET, r2.direction.x, r2.direction.y, r2.direction.z);
	
	// t_ray ray = create_ray(create_point(1, 2, 3), create_vector(0, 1, 0));
	// t_matrix m = scaling(2, 3, 4);
	// t_ray r2 = transform_ray(ray, m);
	// printf(BLU"r2.origin.x: %f %f %f \n"RESET, r2.origin.x, r2.origin.y, r2.origin.z);
	// printf(BLU"r2.direction.y: %f %f %f \n"RESET, r2.direction.x, r2.direction.y, r2.direction.z);

	// t_ray ray = create_ray(create_point(0, 0, 5), create_vector(0, 0, 1));
	// t_sphere sphere = create_sphere();
	// set_transform(&sphere, scaling(2, 2, 2));
	// t_ray r2 = transform_ray(ray, inverse_matrix(&sphere.transform));
	// t_intersections xs = intersect_sphere(sphere, r2);
	// printf(BLU"xs.count: %d\n"RESET, xs.count);
	// if (xs.count > 0)
	// {
	// 	printf("xs.t[0]: %f\n", xs.t[0]);
	// 	printf("xs.t[1]: %f\n", xs.t[1]);
	// }

	// t_ray ray = create_ray(create_point(0, 0, -5), create_vector(0, 0, 1));
	// t_sphere sphere = create_sphere();
	// set_transform(&sphere, m_translation(5, 0, 0));
	// t_ray r2 = transform_ray(ray, inverse_matrix(&sphere.transform));
	// t_intersections xs = intersect_sphere(sphere, r2);
	// printf(BLU"xs.count: %d\n"RESET, xs.count);
	// if (xs.count > 0)
	// {
	// 	printf("xs.t[0]: %f\n", xs.t[0]);
	// 	printf("xs.t[1]: %f\n", xs.t[1]);
	// }
	mlx_hook(data.win_ptr, 17, 1L << 17, close_window, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
		&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
