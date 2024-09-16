#include "minirt.h"

t_ray	transform_ray(t_ray ray, t_matrix transform)
{
	t_ray	result;

	result.origin = matrix_multiply_tuple(transform, ray.origin);
	result.direction = matrix_multiply_tuple(transform, ray.direction);
	printf("Transformed ray origin: %f, %f, %f, %f\n", result.origin.x, result.origin.y,
		result.origin.z, result.origin.w);
	printf("Transformed ray direction: %f, %f, %f, %f\n", result.direction.x,
		result.direction.y, result.direction.z, result.direction.w);
	return (result);
}
