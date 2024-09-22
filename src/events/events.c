#include "minirt.h"

int	handle_no_event(void *data)
{
	(void)data;
	/* This function needs to exist, but it is useless for the moment */
	return (0);
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
	printf("Keypress: %d\n", keysym);
	return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
	(void)data;
	printf("Keyrelease: %d\n", keysym);
	return (0);
}