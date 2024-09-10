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
		t_color color1 = {100, 0, 50};
		t_color color2 = {2, 0, 3};

        // Draw the projectile's position
        int x = (int)(data->proj.position.x * SCALE) + W_WIDTH / 2;  // Scale and center x
        int y = W_HEIGHT - (int)(data->proj.position.y * SCALE) - W_HEIGHT / 2; // Scale and invert y
        if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, add_color(&color1, &color2));
		//printf(BLU"Projectile Position: (%f, %f, %f)\n" RESET, data->proj.position.x, data->proj.position.y, data->proj.position.z);
        // Update projectile
        if (data->proj.position.y > 0) {
			//printf(RED"Projectile Position: (%f, %f, %f)\n" RESET, data->proj.position.x, data->proj.position.y, data->proj.position.z);
            data->proj = tick(&data->env, &data->proj);
        }
    }
    return (0);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	static t_data data;
	t_vector	vector;

	init(&data, &vector);	

	///////// MATRIX CREATION TESTS //////////////////////////

	// double identity_matrix[4][4] = {
	// 	{1, 0, 0, 0}, 
	// 	{0, 1, 0, 0}, 
	// 	{0, 0, 1, 0}, 
	// 	{0, 0, 0, 1}
	// };	
	// t_matrix identity = create_matrix(4);
	// assign_matrix(&identity, identity_matrix);
	// print_matrix(identity, "Identity Matrix", 4);

	t_tuple p = {2, 3, 4, 1};

	t_matrix transform = scaling(-1, 1, 1, 1);
	print_matrix(transform, "Scaling Matrix", 4);

	t_matrix inv = inverse_matrix(&transform);
	print_matrix(inv, "Inverse Matrix", 4);


	t_tuple res = multiply_matrix_by_tuple(&inv, &p);
	printf("Result: %f, %f, %f, %f\n", res.x, res.y, res.z, res.w);


	//t_matrix inv = inverse_matrix(&translation);

	// t_tuple p = {-3, 4, 5, 1};
	// t_tuple result = multiply_matrix_by_tuple(&translation, &p);
	// printf("Result: %f, %f, %f, %f\n", result.x, result.y, result.z, result.w);

	// double m1[4][4] = {
	// 	{-6, 1, 1, 6}, 
    //     {-8, 5, 8, 6}, 
    //     {-1, 0, 8, 2}, 
    //     {-7, 1, -1, 1}
	// };
	// t_matrix matrix = create_matrix(m1);

	// t_matrix matrix4;
	// double m2[4][4] = {
	// 	{3, -9, 7, 3}, 
	// 	{3, -8, 2, -9}, 
	// 	{-4, 4, 4, 1}, 
	// 	{-6, 5, -1, 1}
	// };
	// matrix4 = create_matrix(4);
	// assign_matrix(&matrix4, m2);
	// print_matrix(matrix4, "MAIN Matrix 4", 4);
	
	// t_matrix matrix4b;
	// double m3[4][4] = {
	// 	{8, 2, 2, 2}, 
	// 	{3, -1, 7, 0}, 
	// 	{7, 0, 5, 4}, 
	// 	{6, -2, 0, 5}
	// };
	// matrix4b = create_matrix(4);
	// assign_matrix(&matrix4b, m3);
	// print_matrix(matrix4b, "MAIN Matrix 4", 4);

	// NOT INVERTIBLE MATRIX
	// t_matrix matrix4;
	// double m2[4][4] = {
	// 	{-4, 2, -2, -3}, 
	// 	{9, 6, 2, 6},
	// 	{0, -5, 1, -5},
	// 	{0, 0, 0, 0}
	// };
	// matrix4 = create_matrix(4);
	// assign_matrix(&matrix4, m2);
	// print_matrix(matrix4, "MAIN Matrix 4", 4);

	// t_matrix matrix3;
	// double m3[3][3] = {
	// 	{1, 2, 6},
	// 	{-5, 8, -4},
	// 	{2, 6, 4}
	// };
	// matrix3 = create_matrix(3);
	// assign_matrix_3(&matrix3, m3);
	// print_matrix(matrix3, "MAIN: Matrix 3", 3);

	// double twobytwo_mtrx[2][2] = {
	// 	{1, 5},
	// 	{-3, 2}
	// };
	// double	determinant = calculate_determinant(twobytwo_mtrx);
	// printf("Determinant: %f\n", determinant);	

	///////// MATRIX CALCULATIONS TESTS //////////////////////////
	//calculate_cofactor(&matrix4, 0, 3, 4);
	//calculate_determinant(&matrix4, 4);
	
	// // Inverse Matrix
	// t_tuple tup = {1, 2, 3, 1};
	// t_tuple res = multiply_matrix_by_tuple(&identity, &tup);
	// printf("Result: %f, %f, %f, %f\n", res.x, res.y, res.z, res.w);

	// t_matrix submatrix = find_submatrix(&matrix3, 1, 1, 3);
	// print_matrix(submatrix, "Submatrix in main", 2);

	//calculate_minor(&matrix3, 1, 0, 3);
	//t_matrix result = transpose_matrix(&identity);
	// print_matrix(identity, "Transpose Matrix");

	//printf("Matrix are equal? %d\n", compare_matrix(matrix, matrix2));
	//print_matrix(matrix, "Comparison");
	
	// t_tuple result = multiply_matrix_by_tuple(&identity, &tup_a);
	// printf("Result: %f, %f, %f, %f\n", result.x, result.y, result.z, result.w);


	// Multiply matrix by identity matrix
	//t_matrix result = matrix_multiply(matrix, identity);
	//print_matrix(result);

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
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
	return (0);	
}
