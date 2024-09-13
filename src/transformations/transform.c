#include "minirt.h"

t_ray transform(t_ray *ray, t_matrix *matrix)
{
	t_ray r2;
	
    r2.origin = multiply_matrix_by_tuple(matrix, &ray->origin);
    r2.direction = multiply_matrix_by_tuple(matrix, &ray->direction);

	printf("Transformed ray origin: %f, %f, %f, %f\n", r2.origin.x, r2.origin.y, r2.origin.z, r2.origin.w);
	printf("Transformed ray direction: %f, %f, %f, %f\n", r2.direction.x, r2.direction.y, r2.direction.z, r2.direction.w);
	return(r2);
}