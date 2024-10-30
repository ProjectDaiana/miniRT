#include "minirt.h"

// int	render(t_data *data)
// {
// 	t_canvas	canvas;
// 	t_scene		*scene;
// 	double		aspect_ratio;
// 	t_ray		ray;
// 	t_color		color;
// 	int			color_int;
// 	double		viewport_height;
// 	double		viewport_width;
// 	double		focal_length;
// 	t_tuple		origin;
// 	t_tuple		horizontal;
// 	t_tuple		vertical;
// 	t_tuple		lower_left_corner;
// 	double		u;
// 	double		v;

// 	printf("Starting render...\n");
// 	canvas = create_canvas(W_WIDTH, W_HEIGHT);
// 	scene = &data->scene;
// 	// camera setup
// 	aspect_ratio = (double)W_WIDTH / W_HEIGHT;
// 	viewport_height = 2.0;
// 	viewport_width = aspect_ratio * viewport_height;
// 	focal_length = 1.0;
// 	origin = scene->camera.position;
// 	horizontal = create_vector(viewport_width, 0, 0);
// 	vertical = create_vector(0, viewport_height, 0);
// 	lower_left_corner = tuple_subtract(tuple_subtract(tuple_subtract(origin,
// 					tuple_divide(horizontal, 2)), tuple_divide(vertical, 2)),
// 			create_vector(0, 0, focal_length));
// 	for (int y = 0; y < W_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < W_WIDTH; x++)
// 		{
// 			u = (double)x / (W_WIDTH - 1);
// 			v = (double)(W_HEIGHT - 1 - y) / (W_HEIGHT - 1);
// 			ray.origin = origin;
// 			ray.direction = tuple_normalize(tuple_subtract(tuple_add(tuple_add(lower_left_corner,
// 								tuple_multiply(horizontal, u)),
// 							tuple_multiply(vertical, v)), origin));
// 			color = ray_color(scene, ray);
// 			write_pixel(&canvas, x, y, color);
// 		}
// 	}
// 	printf("Render complete. Converting to MLX image...\n");
// 	// Convert canvas to MLX image
// 	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
// 	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
// 			&data->img.line_length, &data->img.endian);
// 	for (int y = 0; y < W_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < W_WIDTH; x++)
// 		{
// 			color = pixel_at(&canvas, x, y);
// 			color_int = rgb_to_int(color);
// 			my_mlx_pixel_put(&data->img, x, y, color_int);
// 		}
// 	}
// 	printf("Putting image to window...\n");
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
// 	free_canvas(&canvas);
// 	return (0);
// }

// WAS OK

// int	render(t_data *data)
// {
// 	t_canvas	canvas;
// 	t_scene		*scene;
// 	double		aspect_ratio;
// 	t_ray		ray;
// 	t_color		color;
// 	int			color_int;
// 	double		viewport_height;
// 	double		viewport_width;
// 	double		focal_length;
// 	t_tuple		origin;
// 	t_tuple		horizontal;
// 	t_tuple		vertical;
// 	t_tuple		lower_left_corner;
// 	double		u;
// 	double		v;

// 	printf("Starting render...\n");
// 	canvas = create_canvas(W_WIDTH, W_HEIGHT);
// 	scene = &data->scene;
// 	// camera setup
// 	aspect_ratio = (double)W_WIDTH / W_HEIGHT;
// 	viewport_height = 2.0;
// 	viewport_width = aspect_ratio * viewport_height;
// 	focal_length = 1.0;
// 	origin = scene->camera.position;
// 	horizontal = create_vector(viewport_width, 0, 0);
// 	vertical = create_vector(0, viewport_height, 0);
// 	lower_left_corner = tuple_subtract(tuple_subtract(tuple_subtract(origin,
// 					tuple_divide(horizontal, 2)), tuple_divide(vertical, 2)),
// 			create_vector(0, 0, focal_length));
// 	for (int y = 0; y < W_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < W_WIDTH; x++)
// 		{
// 			u = (double)x / (W_WIDTH - 1);
// 			v = (double)(W_HEIGHT - 1 - y) / (W_HEIGHT - 1);
// 			ray.origin = origin;
// 			ray.direction = tuple_normalize(tuple_subtract(tuple_add(tuple_add(lower_left_corner,
// 								tuple_multiply(horizontal, u)),
// 							tuple_multiply(vertical, v)), origin));
// 			color = ray_color(scene, ray);
// 			write_pixel(&canvas, x, y, color);
// 		}
// 	}
// 	printf("Render complete. Converting to MLX image...\n");
// 	// Convert canvas to MLX image
// 	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
// 	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
// 			&data->img.line_length, &data->img.endian);
// 	for (int y = 0; y < W_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < W_WIDTH; x++)
// 		{
// 			color = pixel_at(&canvas, x, y);
// 			color_int = rgb_to_int(color);
// 			my_mlx_pixel_put(&data->img, x, y, color_int);
// 		}
// 	}
// 	printf("Putting image to window...\n");
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
// 	free_canvas(&canvas);
// 	return (0);
// }

t_matrix	look_at(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;
	t_matrix	orientation;
	t_matrix	translation_matrix;
	t_matrix	rotation_matrix;///// Changed

	forward = tuple_normalize(tuple_subtract(to, from));
	left = tuple_cross(tuple_normalize(up), forward);
	true_up = tuple_cross(forward, left);
	orientation = create_matrix(4);
	orientation.m[0][0] = left.x;
	orientation.m[0][1] = left.y;
	orientation.m[0][2] = left.z;
	orientation.m[0][3] = 0;
	orientation.m[1][0] = true_up.x;
	orientation.m[1][1] = true_up.y;
	orientation.m[1][2] = true_up.z;
	orientation.m[1][3] = 0;
	orientation.m[2][0] = -forward.x;
	orientation.m[2][1] = -forward.y;
	orientation.m[2][2] = -forward.z;
	orientation.m[2][3] = 0;
	orientation.m[3][0] = 0;
	orientation.m[3][1] = 0;
	orientation.m[3][2] = 0;
	orientation.m[3][3] = 1;
	translation_matrix = translation(-from.x, -from.y, -from.z);
	rotation_matrix = matrix_multiply(orientation, translation_matrix);////// Changed 
	free_matrix(&orientation, 4);////// Changed 
	free_matrix(&translation_matrix, 4);////// Changed 
	return (rotation_matrix);////// Changed 
}

int	render(t_data *data)
{
	t_canvas canvas = create_canvas(W_WIDTH, W_HEIGHT);
	t_scene *scene = &data->scene;
	t_camera camera = create_camera(W_WIDTH, W_HEIGHT, scene->camera.fov * M_PI
			/ 180.0);
	t_color color;
	t_ray ray;
	int color_int;

	// Set up camera transform
	t_tuple camera_position = scene->camera.position;
	t_tuple camera_look_at = tuple_add(camera_position, scene->camera.orientation);
	t_tuple up = create_vector(0, 1, 0);
	camera.transform = look_at(data->scene.camera.position, camera_look_at, up);
	print_matrix(camera.transform, "Camera Transform", 4);
	printf(GRN"Starting render...\n"RESET);
	// Render the scene
	for (int y = 0; y < W_HEIGHT; y++)
	{
		for (int x = 0; x < W_WIDTH; x++)
		{
			ray = ray_for_pixel(&camera, x, y);
			color = ray_color(scene, ray);
			//printf(GRN"color OK"RESET);
			write_pixel(&canvas, x, y, color);
		}
	}
	free_matrix(&camera.transform, 4);
	printf(GRN"Render complete. Converting to MLX image...\n"RESET);

	// Convert canvas to MLX image
	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	for (int y = 0; y < W_HEIGHT; y++)
	{
		for (int x = 0; x < W_WIDTH; x++)
		{
			color = pixel_at(&canvas, x, y);
			color_int = rgb_to_int(color);
			my_mlx_pixel_put(&data->img, x, y, color_int);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	free_canvas(&canvas);
	return (0);
}