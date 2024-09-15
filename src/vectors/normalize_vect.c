#include "minirt.h"


t_tuple normalize_vect(t_tuple v)
{
	t_tuple	result;
    double		mag;
	
	mag = vect_length(v.x, v.y, v.z);
    if (mag == 0)
		return v;

    result.x = v.x / mag;
    result.y = v.y / mag;
    result.z = v.z / mag;
    return (result);
}