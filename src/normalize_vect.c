#include "minirt.h"

// t_vector normalize_vect(t_vector *vector)
// {
// 	// Avoid division by zero
// 	if (vector->magnitude == 0) {
// 		vector->nx = 0;
// 		vector->ny = 0;
// 		vector->nz = 0;
// 		printf(RED"Error: Division by zero\n" RESET);
// 	}
// 	else
// 	{
// 		vector->nx = vector->x / vector->magnitude;
// 		vector->ny = vector->y / vector->magnitude;
// 		vector->nz = vector->z / vector->magnitude;
// 		printf(YEL"Normalized Vector: %f, %f,
//			%f\n" RESET,vector->nx,vector->ny,vector->nz);
// 	}
// 	return (0);
// }

// t_vector normalize_vect(t_vector v) {
//     double mag = vect_length(v.x, v.y, v.z);
//     if (mag == 0) return (v);  // Avoid division by zero
//     t_vector result;
//     result.x = v.x / mag;
//     result.y = v.y / mag;
//     result.z = v.z / mag;
//     return (result);
// }



