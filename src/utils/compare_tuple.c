#include "minirt.h"

int compare_tuple(t_tuple a, t_tuple b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}