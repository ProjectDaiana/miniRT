#include "minirt.h"

void init_intersections(t_intersections *result)
{
	result->count = 0;
	result->t = malloc(sizeof(double) * result->count);
	result->object = malloc(sizeof(void *) * result->count);
}