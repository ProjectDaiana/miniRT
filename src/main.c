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
	t_vector vector;

	init(&data, &vector);
	t_vector gravity = {0.0, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0};  // Initialize all fields
    t_vector wind = {-0.01, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};    // Initialize all fields
     data.env = (t_env){gravity, wind};

    // Initialize projectile starting one unit above origin
    t_vector initial_position = {0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // Initialize all fields
    t_vector initial_velocity = {1.0, 1.8, 0.0, 0.0, 0.0, 0.0, 0.0};
	vect_multiplication(initial_velocity, 11.25);
    t_vector normalized_velocity = normalize_vect(initial_velocity); // Normalize the velocity
	//printf(GRN"Normalized Vector: %f, %f, %f\n" RESET, vector.nx, vector.ny, vector.nz);
    data.proj = (t_proj){initial_position, normalized_velocity};
	//printf(YEL"Normalized Velocity: (%f, %f, %f)\n" RESET, normalized_velocity.x, normalized_velocity.y, normalized_velocity.z);
	//cross_product_to_array(&a, &b);
	
	///////// MATRIX CREATION

	// double identity_matrix[4][4] = {
	// 	{1, 0, 0, 0}, 
	// 	{0, 1, 0, 0}, 
	// 	{0, 0, 1, 0}, 
	// 	{0, 0, 0, 1}
	// };	
	// t_matrix identity = create_matrix(identity_matrix);

	// double m1[4][4] = {
	// 	{-6, 1, 1, 6}, 
    //     {-8, 5, 8, 6}, 
    //     {-1, 0, 8, 2}, 
    //     {-7, 1, -1, 1}
	// };
	// t_matrix matrix = create_matrix(m1);

	t_matrix matrix4;
	double m2[4][4] = {
	{1, 2, 3, 4}, 
	{5.5, 6.5, 7.5, 8.5}, 
	{9, 10, 11, 12}, 
	{13.5, 14, 15.5, 16.5}
	};
	matrix4 = create_matrix(4);
	assign_matrix(&matrix4, m2);
	print_matrix(matrix4, "Matrix 4", 4);
	
	// double m3[3][3] = {
	// 	{3, 5, 0},
	// 	{2, -1, -7},
	// 	{6, -1, 5}
	// };
	// t_matrix matrix3 = create_matrix_3(m3);


	// double twobytwo_mtrx[2][2] = {
	// 	{1, 5},
	// 	{-3, 2}
	// };
	//double	determinant = calculate_determinant(twobytwo_mtrx);
	//printf("Determinant: %f\n", determinant);

	// t_tuple tup_a = {0.0, 0.0, 20.6, 0};
	// printf("Tuple: %f, %f, %f, %f\n", tup_a.x, tup_a.y, tup_a.z, tup_a.w);
	

	///////// MATRIX CALCULATIONS

	t_matrix submatrix = find_submatrix(&matrix4, 0, 2, 4);
	print_matrix(submatrix, "Submatrix in main", 3);

	calculate_minor(&submatrix, 1, 0, 3);

	//t_matrix result = transpose_matrix(&identity);
	// print_matrix(identity, "Transpose Matrix");

	//printf("Matrix are equal? %d\n", compare_matrix(matrix, matrix2));
	//print_matrix(matrix, "Comparison");
	
	// t_tuple result = multiply_matrix_by_tuple(&identity, &tup_a);
	// printf("Result: %f, %f, %f, %f\n", result.x, result.y, result.z, result.w);


	// Multiply matrix by identity matrix
	//t_matrix result = matrix_multiply(matrix, identity);
	//print_matrix(result);


	//////// MINILIBX
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

// INPUT REFERENCE

// Ambient lighting
// A	ambient lighting ratio in range [0.0,1.0]: 0.2
//		r, g, b

// Camera
// C	x, y, z,
//		3d normalized orientation vector. In range [-1,1] for each x,y,z,
//		FOV  Horizontal field of view in degrees in range [0,180]: 70

// Light
// L	x, y, z,
//		light_brightnes_ratio,
//		r, g, b

// Sphere
// sp 0.0,0.0,20.6 12.6 10,0,255
// sp	x, y, z,
// 		diameter,
// 		r, g, b