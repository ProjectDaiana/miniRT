#include "minirt.h"

// int	handle_no_event(void *data)
// {
// 	(void)data;
// 	/* This function needs to exist, but it is useless for the moment */
// 	return (0);
// }

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit (0);
}
// int	handle_keypress(int keysym, t_data *data)
// {
//     if (keysym == XK_Escape)
//         mlx_destroy_window(data->mlx_ptr, data->win_ptr);
//     printf("Keypress: %d\n", keysym);
//     return (0);
// }

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(0);
	}
	else if (keysym == XK_equal)
	{
		printf(MAG"Camera position"RESET);
		data->scene.camera.position.z += 1;
		render(data);
	}
	else if (keysym == XK_minus)
	{
		printf(MAG"Camera position: %f, %f, %f\n"RESET, data->scene.camera.position.x,
			data->scene.camera.position.y, data->scene.camera.position.z);
		data->scene.camera.position.z -= 1;
		render(data);
	}
	else if (keysym == XK_Up)
	{
		printf(MAG"Camera position: %f, %f, %f\n"RESET, data->scene.camera.position.x,
			data->scene.camera.position.y, data->scene.camera.position.z);
		data->scene.camera.position.y += 1;
		render(data);
	}
	else if (keysym == XK_Down)
	{
		printf(MAG"Camera position: %f, %f, %f\n"RESET, data->scene.camera.position.x,
			data->scene.camera.position.y, data->scene.camera.position.z);
		data->scene.camera.position.y -= 1;
		render(data);
	}
	else if (keysym == XK_Left)
	{
		printf(MAG"Camera position: %f, %f, %f\n"RESET, data->scene.camera.position.x,
			data->scene.camera.position.y, data->scene.camera.position.z);
		data->scene.camera.position.x -= 1;
		render(data);
	}
	else if (keysym == XK_Right)
	{
		printf(MAG"Camera position: %f, %f, %f\n"RESET, data->scene.camera.position.x,
			data->scene.camera.position.y, data->scene.camera.position.z);
		data->scene.camera.position.x += 1;
		render(data);
	}
	// skewing
	// if (keysym == XK_s)
	// {
	// 	t_matrix skew_matrix = skewing(1, 0, 0, 0, 0, 0); // Example skew
	// 	t_matrix scale_matrix = scaling(0.5, 1, 1); // Example scaling
		
	// 	// Multiply the skew_matrix and scale_matrix to the existing camera transform
	// 	data->scene.camera.transform = matrix_multiply(skew_matrix, data->scene.camera.transform);
	// 	data->scene.camera.transform = matrix_multiply(scale_matrix, data->scene.camera.transform);
	// 	print_matrix(data->scene.camera.transform, "Camera Transform After Skewing", 4);
	// 	render(data);
	// }
	// reset camera position
	else if (keysym == XK_r)
	{
		printf(MAG"Camera position: %f, %f, %f\n"RESET, data->scene.camera.position.x,
			data->scene.camera.position.y, data->scene.camera.position.z);
		data->scene.camera.position.x = 0;
		data->scene.camera.position.y = 0;
		data->scene.camera.position.z = -5;
		render(data);
	}
	printf("Keypress: %d\n", keysym);
	return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
	(void)data;
	printf("Keyrelease: %d\n", keysym);
	return (0);
}