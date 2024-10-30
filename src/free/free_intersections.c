#include "minirt.h"

void free_intersections(t_intersections *xs)
{
    if (xs->t)
    {
        free(xs->t);
        xs->t = NULL;
    }
    if (xs->object)
    {
        free(xs->object);
        xs->object = NULL;
    }
    xs->count = 0;
}