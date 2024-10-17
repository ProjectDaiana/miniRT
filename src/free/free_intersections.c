#include "minirt.h"

void free_intersections(t_intersections *xs)
{
	if (xs->count > 0)
	{
		free(xs->t);
		free(xs->object);
	}
}