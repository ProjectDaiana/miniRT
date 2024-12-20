#include "minirt.h"

void	allocate_intersections(t_intersections *result, double *t,
		t_cylinder *cylinder)
{
	int	index;

	result->count = (t[0] != INFINITY) + (t[1] != INFINITY);
	if (result->count > 0)
	{
		result->t = malloc(sizeof(double) * result->count);
		result->object = malloc(sizeof(void *) * result->count);
		index = 0;
		if (t[0] != INFINITY)
			add_valid_intersection(result, t[0], cylinder, &index);
		if (t[1] != INFINITY)
			add_valid_intersection(result, t[1], cylinder, &index);
	}
}

static void	set_orientation_matrix(t_matrix *matrix, t_tuple left,
		t_tuple true_up, t_tuple forward)
{
	if (!matrix || !matrix->m)
		return ;
	matrix->m[0][0] = left.x;
	matrix->m[0][1] = left.y;
	matrix->m[0][2] = left.z;
	matrix->m[0][3] = 0;
	matrix->m[1][0] = true_up.x;
	matrix->m[1][1] = true_up.y;
	matrix->m[1][2] = true_up.z;
	matrix->m[1][3] = 0;
	matrix->m[2][0] = -forward.x;
	matrix->m[2][1] = -forward.y;
	matrix->m[2][2] = -forward.z;
	matrix->m[2][3] = 0;
	matrix->m[3][0] = 0;
	matrix->m[3][1] = 0;
	matrix->m[3][2] = 0;
	matrix->m[3][3] = 1;
}

t_matrix	look_at(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		left;
	t_matrix	orientation;
	t_matrix	trans_matrix;

	forward = tuple_normalize(tuple_subtract(to, from));
	left = tuple_cross(tuple_normalize(up), forward);
	orientation = create_matrix(4);
	set_orientation_matrix(&orientation, left, tuple_cross(forward, left),
		forward);
	trans_matrix = translation(-from.x, -from.y, -from.z);
	return (matrix_multiply(orientation, trans_matrix));
}
