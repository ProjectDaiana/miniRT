#include "minirt.h"

int normalize_vect(t_vector *vector)
{
	// Avoid division by zero
	if (vector->magnitude == 0) {
		vector->nx = 0;
		vector->ny = 0;
		vector->nz = 0;
		printf(RED"Error: Division by zero\n" RESET);
	}
	else
	{
		vector->nx = vector->x / vector->magnitude;
		vector->ny = vector->y / vector->magnitude;
		vector->nz = vector->z / vector->magnitude;
		printf(YEL"Normalized Vector: %f, %f, %f\n" RESET,vector->nx,vector->ny,vector->nz);
	}
	return (0);
}