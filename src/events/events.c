#include "minirt.h"

// int	handle_no_event(void *data)
// {
// 	(void)data;
// 	/* This function needs to exist, but it is useless for the moment */
// 	return (0);
// }

// int	handle_keypress(int keysym, t_data *data)
// {
//     if (keysym == XK_Escape)
//         mlx_destroy_window(data->mlx_ptr, data->win_ptr);
//     printf("Keypress: %d\n", keysym);
//     return (0);
// }

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit (0);
}

void change_cam_position(t_data *data, double *direction, unsigned int key)
{
	t_tuple cam_look_at;
	t_tuple up;

	printf(MAG"Camera position: %f, %f, %f\n"RESET, data->scene.camera.position.x, data->scene.camera.position.y, data->scene.camera.position.z);
	printf(MAG"Camera direction: %f\n"RESET, *direction);
	if (key == XK_Up || key == XK_Right || key == XK_equal)
		*direction += 1;
	else if (key == XK_Down || key == XK_Left || key == XK_minus)
		*direction -= 1;
	cam_look_at = tuple_add(data->scene.camera.position,data->scene.camera.orientation);
	up = create_vector(0, 1, 0);
	data->scene.camera.transform = look_at(data->scene.camera.position, cam_look_at, up);
	printf(MAG"NewCamera position: %f, %f, %f\n"RESET, data->scene.camera.position.x, data->scene.camera.position.y, data->scene.camera.position.z);
	render(data);
}

void reset_cam_position(t_data *data)
{
	data->scene.camera.position.x = 0;
	data->scene.camera.position.y = 0;
	data->scene.camera.position.z = -5;
	printf(MAG"RESET position: %f, %f, %f\n"RESET, data->scene.camera.position.x, data->scene.camera.position.y, data->scene.camera.position.z);
	render(data);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_window(data);
	else if (keysym == XK_equal)
		change_cam_position(data, &data->scene.camera.position.z, keysym);
	else if (keysym == XK_minus)
		change_cam_position(data, &data->scene.camera.position.z, keysym);
	else if (keysym == XK_Up)
		change_cam_position(data, &data->scene.camera.position.y, keysym);
	else if (keysym == XK_Down)
		change_cam_position(data, &data->scene.camera.position.y, keysym);
	else if (keysym == XK_Left)
		change_cam_position(data, &data->scene.camera.position.x, keysym);
	else if (keysym == XK_Right)
		change_cam_position(data, &data->scene.camera.position.x, keysym);
	else if (keysym == XK_r)
		reset_cam_position(data);
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
	printf("Keypress: %d\n", keysym);
	return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
	(void)data;
	printf("Keyrelease: %d\n", keysym);
	return (0);
}
