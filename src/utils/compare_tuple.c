#include "minirt.h"

int compare_tuple(t_tuple a, t_tuple b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}


void init_intersections(t_intersections *result)
{
	result->count = 0;
	result->capacity = 10;
	result->t = malloc(sizeof(double) * result->capacity);
	result->object = malloc(sizeof(void *) * result->capacity);
}