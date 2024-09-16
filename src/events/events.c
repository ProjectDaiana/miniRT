# include "minirt.h"

int	handle_no_event(void *data)
{
	(void)data;
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit (0);
}

int	handle_keypress(int keysym, t_data *data)
{

    if (keysym == XK_Escape)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    printf("Keypress: %d\n", keysym);
    return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
	(void)data;
    printf("Keyrelease: %d\n", keysym);
    return (0);
}