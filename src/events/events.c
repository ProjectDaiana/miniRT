#include "minirt.h"

// int	handle_no_event(void *data)
// {
// 	(void)data;
// 	/* This function needs to exist, but it is useless for the moment */
// 	return (0);
// }

int	close_window(t_data *data)
{
	free_scene(&data->scene);
	free(data->camera.transform.m);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit (0);
}

void reset_cam_position(t_data *data)
{
	data->camera.position.x = 0;
	data->camera.position.y = 0;
	data->camera.position.z = -5;
	printf(MAG"RESET position: %f, %f, %f\n"RESET, data->camera.position.x, data->camera.position.y, data->camera.position.z);
	render(data);
}

void move_camera(t_data *data, t_tuple direction)
{
	t_tuple cam_look_at;
	t_tuple up;

	printf(MAG"num of intersections: %d\n"RESET, data->xs.count);
	data->camera.position.x += direction.x;
	data->camera.position.y += direction.y;
	data->camera.position.z += direction.z;
	cam_look_at = tuple_add(data->camera.position,data->camera.orientation);
	up = create_vector(0, 1, 0);
	//free_matrix(&data->camera.transform);
	data->camera.transform = look_at(data->camera.position, cam_look_at, up);
	render(data);
	printf(MAG"position: %f, %f, %f\n"RESET, data->camera.position.x, data->camera.position.y, data->camera.position.z);
}


int	handle_keypress(int keysym, t_data *data)
{
	t_tuple direction;

	direction = create_vector(0, 0, 0);
	if (keysym == XK_Escape)
		close_window(data);
	else if(keysym == XK_Up)
		direction.y = 1;
	else if(keysym == XK_Down)
		direction.y = -1;
	else if(keysym == XK_Left)
		direction.x = -1;
	else if(keysym == XK_Right)
		direction.x = 1;
	else if(keysym == XK_w)
		direction.z = 1;
	else if(keysym == XK_s)
		direction.z = -1;
	printf("Keypress: %d\n", keysym);
	move_camera(data, direction);
	return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
	(void)data;
	printf("Keyrelease: %d\n", keysym);
	return (0);
}
