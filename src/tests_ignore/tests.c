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

	while (i < 12)
	{
		t_matrix transform = rotation_x(i * M_PI / 6);
		t_tuple res = multiply_matrix_by_tuple(&transform, &p);

		int x = (int)(res.y * SCALE) + W_WIDTH / 2;
		int y = W_HEIGHT - (int)(res.z * SCALE) - W_HEIGHT / 2;
		printf(BLU"Result: %f, %f, %f, %f\n"RESET, res.x, res.y, res.z, res.w);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0xFFFFFF);
		i++;
	}
}

void test_truncated_cylinders()
{
    // Step 1: Create a truncated cylinder
    t_cylinder cyl;
    cyl.min = 1;  // Truncate at y=1
    cyl.max = 2;  // Truncate at y=2

    // Step 2: Define test cases (rays)
    t_ray rays[] = {
        // Test case 1: Ray that misses the cylinder entirely
        create_ray(create_point(0, 1.5, 0), tuple_normalize(create_vector(0.1, 1, 1))),
		// Test case 2: Ray that hits the cylinder
		create_ray(create_point(0, 3, -5), tuple_normalize(create_vector(0, 0, 1))),
		// Test case 3: Ray that hits the cylinder
		create_ray(create_point(0, 0, -5), tuple_normalize(create_vector(0, 0, 01))),
		// Test case 4: Ray that hits the cylinder
		create_ray(create_point(0, 2, -5), tuple_normalize(create_vector(0, 0, 1))),
		// Test case 5: Ray that misses the cylinder
		create_ray(create_point(0, 1, -5), tuple_normalize(create_vector(0, 0, 1))),
		// Test case 6: Ray that hits the cylinder
		create_ray(create_point(0, 1.5, -2), tuple_normalize(create_vector(0, 0, 1))),
	};

	/// Expected intersection counts for each test case
    int expected_counts[] = {0, 0, 0, 0, 0, 2};

    // Step 3: Run each test case and check intersection counts
    for (int i = 0; i < 6; i++)
    {
        t_intersections xs = intersect_cylinder(cyl, rays[i]);

        // Verify if the intersection count matches the expected value
        if (xs.count == expected_counts[i])
        {
            printf(GRN "Test case %d passed!\n" RESET, i + 1);
        }
        else
        {
            printf(RED "Test case %d failed. Expected %d intersections, got %d.\n" RESET,
                   i + 1, expected_counts[i], xs.count);
        }
    }
}