#include "minirt.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	static t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "miniRT");
	if (data.win_ptr == NULL)
		return (MLX_ERROR);
	return (0);	
}


