#include "minirt.h"


void init(t_data *data, t_vector *vector)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	vector->x = 1.0;
	vector->y = 2.0;
	vector->z = 3.0;
	vector->nx = 0.0;
	vector->ny = 0.0;
	vector->nz = 0.0;
	vector->magnitude = vect_length(vector->x, vector->y, vector->z);
	vector->r = 0;
	vector->g = 0;
	vector->b = 0;
	printf(YEL"Vector Magnitude: %f\n" RESET, vector->magnitude);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	static t_data data;
	t_vector vector;

	init(&data, &vector);
	printf(BLU"Vector: %f, %f, %f\n" RESET, vector.x, vector.y, vector.z);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "miniRT");
	if (data.win_ptr == NULL)
	{
		free(data.mlx_ptr);
		return (MLX_ERROR);
	}
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);

	normalize_vect(&vector);

	return (0);	
}
// Input Reference

// A	ambient lighting ratio in range [0.0,1.0]: 0.2
//		r, g, b

// C	x, y, z,
//		3d normalized orientation vector. In range [-1,1] for each x,y,z,
//		FOV  Horizontal field of view in degrees in range [0,180]: 70

// L	x, y, z,
//		light_brightnes_ratio,
//		r, g, b

// sp	x, y, z,
// 		diameter,
// 		r, g, b