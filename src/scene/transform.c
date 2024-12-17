#include "minirt.h"

t_ray	transform_ray(t_ray ray, t_matrix transform)
{
	t_ray	result;

	result.origin = matrix_multiply_tuple(transform, ray.origin);
	result.direction = matrix_multiply_tuple(transform, ray.direction);
	return (result);
}
