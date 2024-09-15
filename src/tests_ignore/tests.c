#include "minirt.h"

int check_rotation_results(t_tuple result_half, t_tuple result_full)
{
	t_tuple expected_half = {0, SQRT2_DIV2, SQRT2_DIV2, 1};
    t_tuple expected_full = {0, 0, 1, 1};
    
    if (fabs(result_half.x - expected_half.x) < 1e-6 && 
        fabs(result_half.y - expected_half.y) < 1e-6 && 
        fabs(result_half.z - expected_half.z) < 1e-6) {
        printf(GRN"Half quarter rotation is correct.\n"RESET);
    } else {
        printf(RED"Half quarter rotation is incorrect.\n"RESET);
    }

    if (fabs(result_full.x - expected_full.x) < 1e-6 && 
        fabs(result_full.y - expected_full.y) < 1e-6 && 
        fabs(result_full.z - expected_full.z) < 1e-6) {
        printf(GRN"Full quarter rotation is correct.\n"RESET);
    } else {
        printf(RED"Full quarter rotation is incorrect.\n"RESET);
    }
	return (0);
}

void draw_clock(t_data *data)
{
	t_tuple p = {0, 0, 1, 1};
	int i = 0;
    int bpp, size_line, endian;
    char *img_data;
	int x;
	int y;

	img_data = mlx_get_data_addr(data->img_ptr, &bpp, &size_line, &endian);
	while (i < 12)
	{
		t_matrix transform = rotation_x(i * M_PI / 6);
		t_tuple res = multiply_matrix_by_tuple(&transform, &p);
		x = (int)(res.y * SCALE) + W_WIDTH / 2;
		y = W_HEIGHT - (int)(res.z * SCALE) - W_HEIGHT / 2;
		if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
        {
            // Calculate pixel index
            int pixel_index = (y * size_line) + (x * (bpp / 8));

            // Set pixel color (white)
            img_data[pixel_index] = 0xFF;        // Blue component
            img_data[pixel_index + 1] = 0xFF;    // Green component
            img_data[pixel_index + 2] = 0xFF;    // Red component
        }
		// x = (int)(res.y * SCALE) + W_WIDTH / 2;
		// y = W_HEIGHT - (int)(res.z * SCALE) - W_HEIGHT / 2;
		// printf(BLU"Result: %f, %f, %f, %f\n"RESET, res.x, res.y, res.z, res.w);
		// mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0xFFFFFF);
		i++;
	}
}