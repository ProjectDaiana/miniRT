#include "minirt.h"

void init(t_data *data, t_vector *vector)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	vector->x = 1.0;
	vector->y = 2.0;
	vector->z = 3.0;
	// vector->nx = 0.0;
	// vector->ny = 0.0;
	// vector->nz = 0.0;
	//vector->magnitude = 0.0;
	// vector->color = (t_color *)malloc(sizeof(t_color));
	// vector->color->r = 0;
	// vector->color->g = 100;
	// vector->color->b = 255;
//	printf(YEL"Vector Magnitude: %f\n" RESET, vector->magnitude);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
// 	static t_data data;
// 	t_vector	vector;

// 	init(&data, &vector);	

// 	///////// MATRIX CREATION TESTS //////////////////////////

// 	double identity_matrix[4][4] = {
// 		{1, 0, 0, 0}, 
// 		{0, 1, 0, 0}, 
// 		{0, 0, 1, 0}, 
// 		{0, 0, 0, 1}
// 	};	
// 	t_matrix identity = create_matrix(4);
// 	assign_matrix(&identity, identity_matrix);
// 	print_matrix(identity, "Identity Matrix", 4);

	
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

// 	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
// 	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
// 	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
// 	mlx_loop(data.mlx_ptr);
// 	return (0);	
// }

int	main(int argc, char **argv)
{
	t_data	data;
	t_scene	scene;

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
	printf("Sphere count: %d\n", scene.sphere_count);
	for (int i = 0; i < scene.sphere_count; i++)
	{
		printf("Sphere %d: center(%f, %f, %f), radius: %f\n", i,
			scene.spheres[i].center.x, scene.spheres[i].center.y,
			scene.spheres[i].center.z, scene.spheres[i].radius);
	}
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "miniRT");
	if (data.win_ptr == NULL)
	{
		free(data.mlx_ptr);
		return (MLX_ERROR);
	}
	data.scene = scene;
	data.img_ptr = mlx_new_image(data.mlx_ptr, W_WIDTH, W_HEIGHT);
	data.addr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	printf("Rendering frame...\n");
	render_img(&data);
	return (0);
}