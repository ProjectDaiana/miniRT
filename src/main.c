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
	vector->magnitude = 0.0;
	// vector->color = (t_color *)malloc(sizeof(t_color));
	// vector->color->r = 0;
	// vector->color->g = 100;
	// vector->color->b = 255;
//	printf(YEL"Vector Magnitude: %f\n" RESET, vector->magnitude);
}

int render(t_data *data)
{
    if (data->win_ptr != NULL)
    {
        // Clear window (optional, may not be necessary every frame)
        //mlx_clear_window(data->mlx_ptr, data->win_ptr);
		draw_clock(data);

		t_color color1 = {100, 0, 50};
		t_color color2 = {2, 0, 3};
		int x = (int)(data->tuple->x * SCALE) + W_WIDTH / 2;
        int y = (int)(data->tuple->y * SCALE) + W_HEIGHT / 2;
		if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, add_color(&color1, &color2));

		}
    }
    return (0);
}

void draw_clock(t_data *data)
{
	t_tuple p = {0, 0, 1, 1};
	int i = 0;

	while (i < 12)
	{
		t_matrix transform = rotation_x(i * PI / 6);
		t_tuple res = multiply_matrix_by_tuple(&transform, &p);

		int x = (int)(res.y * SCALE) + W_WIDTH / 2;
		int y = W_HEIGHT - (int)(res.z * SCALE) - W_HEIGHT / 2;
		printf(BLU"Result: %f, %f, %f, %f\n"RESET, res.x, res.y, res.z, res.w);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0xFFFFFF);
		i++;
	}
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	static t_data data;
	t_vector	vector;

	init(&data, &vector);	

	///////// MATRIX CREATION TESTS //////////////////////////

	double identity_matrix[4][4] = {
		{1, 0, 0, 0}, 
		{0, 1, 0, 0}, 
		{0, 0, 1, 0}, 
		{0, 0, 0, 1}
	};	
	t_matrix identity = create_matrix(4);
	assign_matrix(&identity, identity_matrix);
	print_matrix(identity, "Identity Matrix", 4);

	
	//////// MINILIBX /////////////////////////////
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "miniRT");
	if (data.win_ptr == NULL)
	{
		free(data.mlx_ptr);
		return (MLX_ERROR);
	}
	//// Render the scene
	// CLOCK EXERCISE
	draw_clock(&data);

	
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
	return (0);	
}
