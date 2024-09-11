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