#include "minirt.h"

// t_tuple	normal_at_cylinder(t_cylinder cylinder, t_tuple world_point)
// {
// 	t_tuple	obj_point;
// 	t_tuple	axis_projection;
// 	t_tuple	radial_vect;
// 	double	projection_len;

// 	obj_point = tuple_subtract(world_point, cylinder.center);
// 	projection_len = tuple_dot(obj_point, cylinder.axis);
// 	// Check if point is on caps
// 	if (projection_len >= cylinder.height - EPSILON)
// 		return (cylinder.axis);
// 	if (projection_len <= EPSILON)
// 		return (tuple_negate(cylinder.axis));
// 	// Point is on the body
// 	axis_projection = tuple_multiply(cylinder.axis, projection_len);
// 	radial_vect = tuple_subtract(obj_point, axis_projection);
// 	return (tuple_normalize(radial_vect));
// }

t_tuple	normal_at_cylinder(t_cylinder *cylinder, t_tuple world_point)
{
	t_tuple	obj_point;
	t_tuple	axis_projection;
	t_tuple	radial_vect;
	double	projection_len;

	obj_point = tuple_subtract(world_point, cylinder->center);
	projection_len = tuple_dot(obj_point, cylinder->axis);
	// Check if point is on caps
	if (projection_len >= cylinder->height - EPSILON)
		return (cylinder->axis);
	if (projection_len <= EPSILON)
		return (tuple_negate(cylinder->axis));
	// Point is on the body
	axis_projection = tuple_multiply(cylinder->axis, projection_len);
	radial_vect = tuple_subtract(obj_point, axis_projection);
	return (tuple_normalize(radial_vect));
}

// int	check_cap(t_ray ray, double t, t_cylinder cylinder)
// {
// 	t_tuple	point;
// 	t_tuple	to_point;
// 	t_tuple	axis_projection;
// 	t_tuple	orthogonal_vect;
// 	double	distance_from_axis;
// 	double	radius;

// 	radius = cylinder.diameter / 2;
// 	point = tuple_add(ray.origin, tuple_multiply(ray.direction, t));
// 	to_point = tuple_subtract(point, cylinder.center);
// 	axis_projection = tuple_multiply(cylinder.axis, tuple_dot(to_point,
// 				cylinder.axis));
// 	orthogonal_vect = tuple_subtract(to_point, axis_projection);
// 	distance_from_axis = tuple_dot(orthogonal_vect, orthogonal_vect);
// 	return (distance_from_axis <= pow(radius, 2));
// }

int	check_cap(t_ray ray, double t, t_cylinder cylinder)
{
	t_tuple	point;
	t_tuple	to_point;
	double	distance_from_axis;
	double	radius;

	radius = cylinder.diameter / 2;
	point = tuple_add(ray.origin, tuple_multiply(ray.direction, t));
	to_point = tuple_subtract(point, cylinder.center);
	// Project point onto cylinder axis
	distance_from_axis = sqrt(tuple_dot(to_point, to_point)
			- pow(tuple_dot(to_point, cylinder.axis), 2));
	return (distance_from_axis <= radius);
}

void	add_intersection(t_intersections *result, double t)
{
	double	*new_t;

	if (result->count == 0)
	{
		result->t = ft_calloc(1, sizeof(double));
	}
	else
	{
		new_t = ft_calloc(result->count + 1, sizeof(double));
		if (!new_t)
		{
			fprintf(stderr,
				"Error: Memory allocation failed in add_intersection\n");
			exit(1);
		}
		ft_memcpy(new_t, result->t, sizeof(double) * result->count);
		free(result->t);
		result->t = new_t;
	}
	if (!result->t)
	{
		fprintf(stderr,
			"Error: Memory allocation failed in add_intersection\n");
		exit(1);
	}
	result->t[result->count] = t;
	result->count++;
}

// void	intersect_caps(t_cylinder cylinder, t_ray ray, t_intersections *result)
// {
// 	double	t_min;
// 	double	t_max;
// 	double	origin_projection;
// 	double	direction_projection;
// 	t_tuple	axis_normal;

// 	axis_normal = tuple_normalize(cylinder.axis);
// 	origin_projection = tuple_dot(tuple_subtract(ray.origin, cylinder.center),
// 			axis_normal);
// 	direction_projection = tuple_dot(ray.direction, axis_normal);
// 	t_min = (cylinder.min - origin_projection) / direction_projection;
// 	t_max = (cylinder.max - origin_projection) / direction_projection;
// 	if (check_cap(ray, t_min, cylinder))
// 		add_intersection(result, t_min + EPSILON);
// 	if (check_cap(ray, t_max, cylinder))
// 		add_intersection(result, t_max + EPSILON);
// }

void	intersect_caps(t_cylinder cylinder, t_ray ray, t_intersections *result)
{
	double	t;
	double	direction_dot;

	direction_dot = tuple_dot(ray.direction, cylinder.axis);
	if (fabs(direction_dot) < EPSILON)
		return ;
	// Bottom cap
	t = tuple_dot(tuple_subtract(tuple_add(cylinder.center,
					tuple_multiply(cylinder.axis, 0)), ray.origin),
			cylinder.axis) / direction_dot;
	if (check_cap(ray, t, cylinder))
		add_intersection(result, t);
	// Top cap
	t = tuple_dot(tuple_subtract(tuple_add(cylinder.center,
					tuple_multiply(cylinder.axis, cylinder.height)),
				ray.origin), cylinder.axis) / direction_dot;
	if (check_cap(ray, t, cylinder))
		add_intersection(result, t);
}

// void	calculate_t(double *t1, double *t2, double discriminant, double a,
// 		double b)
// {
// 	double	temp;

// 	if (fabs(a) < EPSILON)
// 	{
// 		*t1 = *t2 = INFINITY;
// 		return ;
// 	}
// 	*t1 = (-b - sqrt(discriminant)) / (2 * a);
// 	*t2 = (-b + sqrt(discriminant)) / (2 * a);
// 	if (fabs(*t1 - *t2) > EPSILON && *t1 > *t2)
// 	{
// 		temp = *t1;
// 		*t1 = *t2;
// 		*t2 = temp;
// 	}
// }

void	calculate_t(double *t1, double *t2, double discriminant, double a,
		double b)
{
	double	temp;

	if (fabs(a) < EPSILON)
	{
		*t1 = *t2 = INFINITY;
		return ;
	}
	*t1 = (-b - sqrt(discriminant)) / (2 * a);
	*t2 = (-b + sqrt(discriminant)) / (2 * a);
	// Ensure t1 is always the smaller value
	if (*t1 > *t2)
	{
		temp = *t1;
		*t1 = *t2;
		*t2 = temp;
	}
}

// void	intersect_body(double a, double b, double c, t_intersections *result,
// 		t_cylinder cylinder, t_ray ray)
// {
// 	double	discriminant;
// 	double	t1;
// 	double	t2;
// 	double	origin_projection;
// 	double	direction_projection;
// 	double	y1;
// 	double	y2;

// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant > 0)
// 	{
// 		calculate_t(&t1, &t2, discriminant, a, b);
// 		origin_projection = tuple_dot(tuple_subtract(ray.origin,
// 					cylinder.center), cylinder.axis);
// 		direction_projection = tuple_dot(ray.direction, cylinder.axis);
// 		y1 = origin_projection + t1 * direction_projection;
// 		y2 = origin_projection + t2 * direction_projection;
// 		if (y1 >= cylinder.min && y1 <= cylinder.max)
// 		{
// 			add_intersection(result, t1);
// 		}
// 		if (y2 >= cylinder.min && y2 <= cylinder.max)
// 		{
// 			add_intersection(result, t2);
// 		}
// 	}
// }

void	intersect_body(double a, double b, double c, t_intersections *result,
		t_cylinder cylinder, t_ray ray)
{
	double	discriminant;
	double	t1;
	double	t2;
	double	y1;
	double	y2;
	t_tuple	p1;
	t_tuple	p2;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	calculate_t(&t1, &t2, discriminant, a, b);
	// Calculate intersection points' positions along cylinder axis
	p1 = tuple_add(ray.origin, tuple_multiply(ray.direction, t1));
	p2 = tuple_add(ray.origin, tuple_multiply(ray.direction, t2));
	y1 = tuple_dot(tuple_subtract(p1, cylinder.center), cylinder.axis);
	y2 = tuple_dot(tuple_subtract(p2, cylinder.center), cylinder.axis);
	if (y1 >= 0 && y1 <= cylinder.height)
		add_intersection(result, t1);
	if (y2 >= 0 && y2 <= cylinder.height)
		add_intersection(result, t2);
}

// t_intersections	intersect_cylinder(t_cylinder cylinder, t_ray ray)
// {
// 	t_intersections	result;
// 	t_tuple			oc;
// 	double			a;
// 	double			b;
// 	double			c;

// 	result.count = 0;
// 	result.t = NULL;
// 	result.object = NULL;
// 	oc = tuple_subtract(ray.origin, cylinder.center);
// 	a = tuple_dot(ray.direction, ray.direction) - pow(tuple_dot(ray.direction,
// 				cylinder.axis), 2);
// 	b = 2 * (tuple_dot(ray.direction, oc) - tuple_dot(ray.direction,
// 				cylinder.axis) * tuple_dot(oc, cylinder.axis));
// 	c = tuple_dot(oc, oc) - pow(tuple_dot(oc, cylinder.axis), 2)
// 		- pow(cylinder.diameter / 2, 2);
// 	intersect_body(a, b, c, &result, cylinder, ray);
// 	intersect_caps(cylinder, ray, &result);
// 	return (result);
// }
