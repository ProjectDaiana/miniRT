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

	//t_tuple p = {2, 3, 4, 1};

	// t_matrix transform = scaling(-1, 1, 1, 1);
	// print_matrix(transform, "Scaling Matrix", 4);

	// t_matrix inv = inverse_matrix(&transform);
	// print_matrix(inv, "Inverse Matrix", 4);


	// t_tuple res = multiply_matrix_by_tuple(&inv, &p);
	// printf("Result: %f, %f, %f, %f\n", res.x, res.y, res.z, res.w);


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

	// CHAINING TRANSFORMATIONS TESTS
	// t_tuple p = {1, 0, 1, 1};

	// t_matrix a = rotation_x(PI / 2);
	// t_matrix b = scaling(5, 5, 5);
	// t_matrix c = translation(10, 5, 7);

	// t_matrix t = matrix_multiply(matrix_multiply(c, b), a);
	// t_tuple res = multiply_matrix_by_tuple(&t, &p);
	// printf(GRN"Result: %f, %f, %f, %f\n"RESET, res.x, res.y, res.z, res.w);

	//SKEW TESTS
	// t_matrix skew = skewing(0, 0, 0, 0, 0, 1);
	// t_tuple skw_p = multiply_matrix_by_tuple(&skew, &p);
    // printf("Result: %f, %f, %f, %f\n", skw_p.x, skw_p.y, skw_p.z, skw_p.w);

	/// ROTATION TESTS //////////////////////////
	//t_matrix half_quarter = rotation_x(PI / 4);
	//t_matrix full_quarter = rotation_(PI / 2);
	//t_matrix inv = inverse_matrix(&half_quarter);

 	//t_tuple result_half = multiply_matrix_by_tuple(&half_quarter, &p);
//    t_tuple result_full = multiply_matrix_by_tuple(&full_quarter, &p);
    
    // Output the results
//    printf(YEL"Result of half quarter rotation: (%f, %f, %f, %f)\n", result_half.x, result_half.y, result_half.z, result_half.w);
    //printf(YEL"Result of full quarter rotation: (%f, %f, %f, %f)\n", result_full.x, result_full.y, result_full.z, result_full.w);
	//check_rotation_results(result_half, result_full);	



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
	//// Render the scene
	// CLOCK EXERCISE
	draw_clock(&data);

	
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
	return (0);	
}
