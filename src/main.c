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
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, multiply_color_by_color(&color1, &color2));
		//printf(BLU"Projectile Position: (%f, %f, %f)\n" RESET, data->proj.position.x, data->proj.position.y, data->proj.position.z);
        // Update projectile
        if (data->proj.position.y > 0) {
			printf(RED"Projectile Position: (%f, %f, %f)\n" RESET, data->proj.position.x, data->proj.position.y, data->proj.position.z);
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

// Input Reference

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
// sp	x, y, z,
// 		diameter,
// 		r, g, b