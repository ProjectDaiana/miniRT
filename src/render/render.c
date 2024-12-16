#include "minirt.h"

// // int	render(t_data *data)
// // {
// // 	t_scene			scene;
// // 	t_canvas		canvas;
// // 	double			aspect_ratio;
// // 	double			half_view;
// // 	double			half_width;
// // 	double			half_height;
// // 	double			pixel_size;
// // 	t_tuple			camera_forward;
// // 	t_tuple			camera_left;
// // 	t_tuple			camera_up;
// // 	double			world_x;
// // 	double			world_y;
// // 	t_tuple			pixel;
// // 	t_ray			ray;
// // 	t_intersections	xs;
// // 	t_tuple			point;
// // 	t_tuple			normal;
// // 	t_tuple			eye;
// // 	t_color			color;
// // 	int				bits_per_pixel;
// // 	int				size_line;
// // 	int				endian;
// // 	int				color_int;

// // 	(void)data;
// // 	parse_scene("sphere.rt", &scene);
// // 	canvas = create_canvas(W_WIDTH, W_HEIGHT);
// // 	aspect_ratio = (double)W_WIDTH / W_HEIGHT;
// // 	half_view = tan(scene.camera.fov / 2);
// // 	half_width = aspect_ratio * half_view;
// // 	half_height = half_view;
// // 	pixel_size = (half_width * 2) / W_WIDTH;
// // 	camera_forward = tuple_normalize(tuple_subtract(scene.camera.orientation,
// // 				scene.camera.position));
// // 	camera_left = tuple_normalize(tuple_cross(create_vector(0, 1, 0),
// // 				camera_forward));
// // 	camera_up = tuple_cross(camera_forward, camera_left);
// // 	for (int y = 0; y < W_HEIGHT; y++)
// // 	{
// // 		for (int x = 0; x < W_WIDTH; x++)
// // 		{
// // 			world_x = half_width - pixel_size * x;
// // 			world_y = half_height - pixel_size * y;
// // 			pixel = tuple_add(scene.camera.position,
// // 					tuple_add(tuple_multiply(camera_forward, 1),
// // 						tuple_add(tuple_multiply(camera_left, world_x),
// // 							tuple_multiply(camera_up, world_y))));
// // 			ray = create_ray(scene.camera.position,
// // 					tuple_normalize(tuple_subtract(pixel,
// // 							scene.camera.position)));
// // 			xs = intersect_sphere(scene.sphere, ray);
// // 			if (xs.count > 0)
// // 			{
// // 				point = position(ray, xs.t1);
// // 				normal = normal_at(scene.sphere, point);
// // 				eye = tuple_negate(ray.direction);
// // 				color = lighting(scene.sphere.material, scene.light.position,
// // 						scene.light.color, point, eye, normal);
// // 				write_pixel(&canvas, x, y, color);
// // 			}
// // 			else
// // 			{
// // 				write_pixel(&canvas, x, y, create_color(0, 0, 0));
// // 			}
// // 		}
// // 	}
// // 	// Convert canvas to MLX image
// // 	bits_per_pixel = 32;
// // 	size_line = W_WIDTH * 4;
// // 	endian = 0;
// // 	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
//
// 	// data->img.addr = mlx_get_data_addr(data->img.img,&data->img.bits_per_pixel,
// // 	// 		&data->img.line_length, &data->img.endian);
// // 	data->img.addr = mlx_get_data_addr(data->img.img, &bits_per_pixel,
// // 			&size_line, &endian);
// // 	for (int y = 0; y < W_HEIGHT; y++)
// // 	{
// // 		for (int x = 0; x < W_WIDTH; x++)
// // 		{
// // 			color = pixel_at(&canvas, x, y);
// // 			color_int = ((int)(color.r * 255) << 16) | ((int)(color.g
// // 						* 255) << 8) | ((int)(color.b * 255));
// // 			my_mlx_pixel_put(&data->img, x, y, color_int);
// // 		}
// // 	}
// // 	// Put the image to the window
// // 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0,
//		0);
// // 	free_canvas(&canvas);
// // 	return (0);
// // }

// // int	render(t_data *data)
// // {
// // 	t_scene			scene;
// // 	t_canvas		canvas;
// // 	t_sphere		sphere;
// // 	t_tuple			light_position;
// // 	t_color			light_color;
// // 	int				bits_per_pixel;
// // 	int				size_line;
// // 	int				endian;
// // 	double			world_x;
// // 	t_tuple			pixel;
// // 	t_tuple			origin;
// // 	t_tuple			direction;
// // 	t_ray			ray;
// // 	t_intersections	xs;
// // 	t_tuple			point;
// // 	t_tuple			normal;
// // 	t_tuple			eye;
// // 	t_color			color;
// // 	int				color_int;

// // 	parse_scene("sphere.rt", &scene);
// // 	canvas = create_canvas(W_WIDTH, W_HEIGHT);
// // 	sphere = create_sphere();
// // 	light_position = create_point(-10, 10, -10);
// // 	light_color = create_color(1, 1, 1);
// // 	// Create an MLX image
// // 	bits_per_pixel = 32;
// // 	size_line = W_WIDTH * 4;
// // 	endian = 0;
// // 	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
// // 	data->img.addr = mlx_get_data_addr(data->img.img, &bits_per_pixel,
// // 			&size_line, &endian);
// // 	for (int y = 0; y < W_HEIGHT; y++)
// // 	{
// // 		for (int x = 0; x < W_WIDTH; x++)
// // 		{
// // 			world_x = (double)x / W_WIDTH * 2 - 1;
// // 			double world_y = 1 - (double)y / W_HEIGHT * 2; // Flip y-axis
// // 			pixel = create_point(world_x, world_y, 10);
// // 			origin = create_point(0, 0, -5);
// // 			direction = tuple_normalize(tuple_subtract(pixel, origin));
// // 			ray = create_ray(origin, direction);
// // 			xs = intersect_sphere(sphere, ray);
// // 			if (xs.count > 0)
// // 			{
// // 				point = position(ray, xs.t1);
// // 				normal = normal_at(sphere, point);
// // 				eye = tuple_negate(direction);
// // 				color = lighting(sphere.material, light_position,
//						light_color,
// // 						point, eye, normal);
// // 				// Convert color to integer and put pixel in image
// // 				color_int = ((int)(color.r * 255) << 16) | ((int)(color.g
// // 							* 255) << 8) | ((int)(color.b * 255));
// // 				my_mlx_pixel_put(&data->img, x, y, color_int);
// // 			}
// // 			else
// // 			{
// // 				// Background color (black)
// // 				my_mlx_pixel_put(&data->img, x, y, 0x000000);
// // 			}
// // 		}
// // 	}
// // 	// Put the image to the window
// // 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0,
//		0);
// // 	return (0);
// // }

// int	render(t_data *data)
// {
// 	t_canvas		canvas;
// 	t_sphere		sphere;
// 	t_tuple			light_position;
// 	t_color			light_color;
// 	double			world_x;
// 	t_tuple			pixel;
// 	// t_tuple			direction;
// 	t_ray			ray;
// 	t_intersections	xs;
// 	t_tuple			point;
// 	t_tuple			normal;
// 	t_tuple			eye;
// 	t_color			color;
// 	int				color_int;
// 	t_tuple			camera_position;
// 	double			fov;
// 	t_tuple			camera_direction;
// 	double			aspect_ratio;
// 	double			half_view;
// 	double			half_width;
// 	double			half_height;
// 	double			pixel_size;
// 	t_tuple			up;
// 	t_tuple			forward;
// 	t_tuple			right;
// 	t_tuple			true_up;
// 	double			xoffset;
// 	double			yoffset;
// 	double			world_y;

// 	// t_tuple			origin;
// 	// t_scene			scene;
// 	printf("Rendering scene...\n");
// 	printf("Sphere position: %f, %f, %f\n", data->scene.spheres[0].center.x,
// 		data->scene.spheres[0].center.y, data->scene.spheres[0].center.z);
// 	printf("Light position: %f, %f, %f\n", data->scene.light.position.x,
// 		data->scene.light.position.y, data->scene.light.position.z);
// 	// parse_scene("sphere.rt", &scene);
// 	canvas = create_canvas(W_WIDTH, W_HEIGHT);
// 	// sphere = create_sphere();
// 	// light_position = create_point(-10, 10, -10);
// 	// light_color = create_color(1, 1, 1);
// 	sphere = data->scene.spheres[0];
// 	// Use the first sphere from the parsed scene
// 	light_position = data->scene.light.position;
// 	light_color = data->scene.light.color;
// 	camera_position = data->scene.camera.position;
// 	camera_direction = data->scene.camera.orientation;
// 	fov = data->scene.camera.fov * M_PI / 180.0;
// 	aspect_ratio = (double)W_WIDTH / W_HEIGHT;
// 	half_view = tan(fov / 2);
// 	half_width = aspect_ratio * half_view;
// 	half_height = half_view;
// 	pixel_size = (half_width * 2) / W_WIDTH;
// 	up = create_vector(0, 1, 0);
// 	forward = tuple_normalize(camera_direction);
// 	right = tuple_cross(forward, up);
// 	true_up = tuple_cross(right, forward);
// 	for (int y = 0; y < W_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < W_WIDTH; x++)
// 		{
// 			// world_x = (double)x / W_WIDTH * 2 - 1;
// 			// double world_y = 1 - (double)y / W_HEIGHT * 2; // Flip y-axis
// 			// pixel = create_point(world_x, world_y, 1);
// 			// // origin = create_point(0, 0, -5);
// 			// // direction = tuple_normalize(tuple_subtract(pixel, origin));
// 			// direction = tuple_normalize(tuple_subtract(pixel,
// 			//			camera_position));
// 			// // ray = create_ray(origin, direction);
// 			xoffset = (x + 0.5) * pixel_size;
// 			yoffset = (y + 0.5) * pixel_size;
// 			world_x = half_width - xoffset;
// 			world_y = half_height - yoffset;
// 			pixel = tuple_add(camera_position,
// 					tuple_subtract(tuple_add(tuple_add(tuple_multiply(right,
// 									world_x), tuple_multiply(true_up, world_y)),
// 							forward), camera_position));
// 			ray = create_ray(camera_position,
// 					tuple_normalize(tuple_subtract(pixel, camera_position)));
// 			xs = intersect_sphere(sphere, ray);
// 			if (xs.count > 0)
// 			{
// 				point = position(ray, xs.t1);
// 				normal = normal_at(sphere, point);
// 				// eye = tuple_negate(direction);
// 				eye = tuple_negate(ray.direction);
// 				color = lighting(sphere.material, light_position, light_color,
// 						point, eye, normal);
// 				write_pixel(&canvas, x, y, color);
// 			}
// 			else
// 			{
// 				write_pixel(&canvas, x, y, create_color(0, 0, 0));
// 			}
// 		}
// 	}
// 	// Convert canvas to MLX image
// 	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
// 	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
// 			&data->img.line_length, &data->img.endian);
// 	for (int y = 0; y < W_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < W_WIDTH; x++)
// 		{
// 			color = pixel_at(&canvas, x, y);
// 			color_int = ((int)(color.r * 255) << 16) | ((int)(color.g
// 						* 255) << 8) | ((int)(color.b * 255));
// 			my_mlx_pixel_put(&data->img, x, y, color_int);
// 		}
// 	}
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
	return (matrix_multiply(orientation, translation_matrix));
}

// ok
// int	render(t_data *data)
// {
// 	t_canvas	canvas;
// 	t_scene		*scene;
// 	t_camera	camera;
// 	t_color		color;
// 	t_ray		ray;
// 	int			color_int;
// 	t_tuple		camera_position;
// 	t_tuple		camera_look_at;
// 	t_tuple		up;

// 	canvas = create_canvas(W_WIDTH, W_HEIGHT);
// 	scene = &data->scene;
// 	camera = create_camera(W_WIDTH, W_HEIGHT, scene->camera.fov * M_PI / 180.0);
// 	// Set up camera transform
// 	camera_position = scene->camera.position;
// 	camera_look_at = tuple_add(camera_position, scene->camera.orientation);
// 	up = create_vector(0, 1, 0);
// 	camera.transform = look_at(camera_position, camera_look_at, up);
// 	// Render the scene
// 	for (int y = 0; y < W_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < W_WIDTH; x++)
// 		{
// 			ray = ray_for_pixel(&camera, x, y);
// 			color = ray_color(scene, ray, 0);
// 			write_pixel(&canvas, x, y, color);
// 		}
// 	}
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
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
// 	free_canvas(&canvas);
// 	return (0);
// }

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
	t_tuple camera_look_at = tuple_add(camera_position,
			scene->camera.orientation);
	t_tuple up = create_vector(0, 1, 0);
	camera.transform = look_at(camera_position, camera_look_at, up);

	// Render the scene
	for (int y = 0; y < W_HEIGHT; y++)
	{
		for (int x = 0; x < W_WIDTH; x++)
		{
			ray = ray_for_pixel(&camera, x, y);
			color = ray_color(scene, ray);
			write_pixel(&canvas, x, y, color);
		}
	}

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
