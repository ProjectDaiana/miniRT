#include "minirt.h"

t_tuple	normal_at_cylinder(t_cylinder cylinder, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;

	object_point = tuple_subtract(world_point, cylinder.center);
	object_normal = tuple_normalize(object_point);
	return (object_normal);
}

// t_tuple	normal_at_cylinder(t_cylinder cylinder, t_tuple point)
// {
// 	t_tuple	pc;
// 	double	projection;
// 	t_tuple	axis_point;

// 	pc = tuple_subtract(point, cylinder.center);
// 	projection = tuple_dot(pc, cylinder.axis);
// 	axis_point = tuple_add(cylinder.center, tuple_multiply(cylinder.axis,
// 				projection));
// 	return (tuple_normalize(tuple_subtract(point, axis_point)));
// }

// int	check_cap(t_ray ray, double t, t_cylinder cylinder)
// {
// 	t_tuple	point;
// 	t_tuple dist_vector;
// 	double	dist_from_axis;
	

// 	point = tuple_add(ray.origin, tuple_multiply(ray.direction, t));
// 	dist_vector = tuple_subtract(point, create_point(cylinder.center.x, point.y,
// 				cylinder.center.z));
// 	dist_from_axis = pow(point.x - cylinder.center.x, 2) + pow(point.z - cylinder.center.z, 2);
// 	return (dist_from_axis <= pow(cylinder.diameter / 2, 2));
// }

// void	intersect_caps(t_cylinder cylinder, t_ray ray, t_intersections *result)
// {
// 	double t_min;
// 	double t_max;

// 	t_min = (cylinder.min - ray.origin.y) / ray.direction.y;
// 	t_max = (cylinder.max - ray.origin.y) / ray.direction.y;
// 	if (check_cap(ray, t_min, cylinder))
// 	{
// 		result->count++;
// 		result->t = realloc(result->t, sizeof(double) * result->count);
// 		result->object = realloc(result->object, sizeof(void *) * result->count);
// 		result->t[result->count - 1] = t_min;
// 		result->object[result->count - 1] = &cylinder;
// 	}
// 	if (check_cap(ray, t_max, cylinder))
// 	{
// 		result->count++;
// 		result->t = realloc(result->t, sizeof(double) * result->count);
// 		result->object = realloc(result->object, sizeof(void *) * result->count);
// 		result->t[result->count - 1] = t_max;
// 		result->object[result->count - 1] = &cylinder;
// 	}
// }

// Caps in Y axis
int check_cap(t_ray ray, double t, t_cylinder cylinder)
{
	t_tuple	point;
	double	distance_from_axis;
    // Calculate the point of intersection
    point = tuple_add(ray.origin, tuple_multiply(ray.direction, t));
    // Compute the distance from the cylinder's axis (which is the center of the cap)
	distance_from_axis = pow(point.x - cylinder.center.x, 2) + pow(point.z - cylinder.center.z, 2);

    // If the distance from the axis is less than or equal to the radius squared, it's within the cap
    return (distance_from_axis <= pow(cylinder.diameter / 2, 2));
}

void intersect_caps(t_cylinder cylinder, t_ray ray, t_intersections *result)
{
	double	t_min;
	double	t_max;
    // Check intersection with the bottom cap (min)
    t_min = (cylinder.min - ray.origin.y) / ray.direction.y;
    if (check_cap(ray, t_min, cylinder))
	{
		printf(RED"BOTTOM CAP t_min: %f\n"RESET, t_min);
        result->count++;
        result->t = realloc(result->t, sizeof(double) * result->count);
        result->object = realloc(result->object, sizeof(void *) * result->count);
        result->t[result->count - 1] = t_min;
        result->object[result->count - 1] = &cylinder;
    }
    // Check intersection with the top cap (max)
	t_max = (cylinder.max - ray.origin.y) / ray.direction.y;
    if (check_cap(ray, t_max, cylinder))
	{
        result->count++;
        result->t = realloc(result->t, sizeof(double) * result->count);
        result->object = realloc(result->object, sizeof(void *) * result->count);
        result->t[result->count - 1] = t_max;
        result->object[result->count - 1] = &cylinder;
    }
}

// Trying with different axis but no success
// int	check_cap(t_ray ray, double t, t_cylinder cylinder, t_tuple cap_center)
// {
// 	t_tuple	point;
// 	t_tuple dist_vector;
// 	double	dist_from_axis;

// 	point = tuple_add(ray.origin, tuple_multiply(ray.direction, t));
// 	dist_vector = tuple_subtract(point, cap_center);
// 	dist_from_axis = tuple_dot(dist_vector, dist_vector);
// 	return (dist_from_axis <= pow(cylinder.diameter / 2, 2));
// }

// void	intersect_caps(t_cylinder cylinder, t_ray ray, t_intersections *result)
// {
// 	double t_min;
// 	double t_max;
// 	t_tuple cap_normal;
// 	t_tuple cap_min_center;
// 	t_tuple cap_max_center;

// 	cap_normal = cylinder.axis;
// 	cap_min_center = tuple_add(cylinder.center, tuple_multiply(cylinder.axis, cylinder.min));
// 	cap_max_center = tuple_add(cylinder.center, tuple_multiply(cylinder.axis, cylinder.max));

// 	t_min = tuple_dot(tuple_subtract(cap_min_center, ray.origin), cap_normal)
// 		/ tuple_dot(ray.direction, cap_normal);
// 	if (check_cap(ray, t_min, cylinder, cap_min_center))
// 	{
// 		result->count++;
// 		result->t = realloc(result->t, sizeof(double) * result->count);
// 		result->object = realloc(result->object, sizeof(void *) * result->count);
// 		result->t[result->count - 1] = t_min;
// 		result->object[result->count - 1] = &cylinder;
// 	}
// 	t_max = tuple_dot(tuple_subtract(cap_max_center, ray.origin), cap_normal)
// 		/ tuple_dot(ray.direction, cap_normal);
// 	if (check_cap(ray, t_max, cylinder, cap_max_center))
// 	{
// 		result->count++;
// 		result->t = realloc(result->t, sizeof(double) * result->count);
// 		result->object = realloc(result->object, sizeof(void *) * result->count);
// 		result->t[result->count - 1] = t_max;
// 		result->object[result->count - 1] = &cylinder;
// 	}

// }