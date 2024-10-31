#include "minirt.h"

t_tuple normal_at_cylinder(t_cylinder cylinder, t_tuple world_point)
{
	t_tuple	obj_point;
	t_tuple	axis_projection;
	t_tuple radial_vect;
	double projection_len;

	obj_point = tuple_subtract(world_point, cylinder.center);
	axis_projection = tuple_multiply(cylinder.axis, tuple_dot(obj_point, cylinder.axis));
	radial_vect = tuple_subtract(obj_point, axis_projection);
	projection_len = tuple_dot(obj_point, cylinder.axis);
	if (projection_len >= cylinder.max)
		return (tuple_normalize(cylinder.axis));
	if (projection_len <= cylinder.min)
		return(tuple_normalize(tuple_negate(cylinder.axis)));
	return (tuple_normalize(radial_vect));
}

int check_cap(t_ray ray, double t, t_cylinder cylinder)
{
	t_tuple	point;
	t_tuple	to_point;
	t_tuple	axis_projection;
	t_tuple orthogonal_vect;
	double	distance_from_axis;
	double radius;

	radius = cylinder.diameter / 2;
	point = tuple_add(ray.origin, tuple_multiply(ray.direction, t));
	to_point = tuple_subtract(point, cylinder.center);
	axis_projection = tuple_multiply(cylinder.axis, tuple_dot(to_point, cylinder.axis));
	orthogonal_vect = tuple_subtract(to_point, axis_projection);
	distance_from_axis = tuple_dot(orthogonal_vect, orthogonal_vect);
	return (distance_from_axis <= pow(radius, 2));
	//return (distance_from_axis <= pow(cylinder.diameter / 2, 2));
}

void add_intersection(t_intersections *result, double t)
{
	//printf(BLU"count: %d\n"RESET, result->count);
	if (result->count == 0)
	{
		//printf(GRN"FT_CALLOC!!!!!! count: %d\n"RESET, result->count);
		result->t = ft_calloc(1, sizeof(double));
		//result->object = ft_calloc(1, sizeof(void *));
	}
	else
	{
		//printf(MAG"ft_memcpy!!!!!! count: %d\n"RESET, result->count);
		double *new_t = ft_calloc(result->count + 1, sizeof(double));
		//void **new_object = ft_calloc(result->count + 1, sizeof(void *));
		if(!new_t)
		{
			fprintf(stderr, "Error: Memory allocation failed in add_intersection\n");
			exit(1);
		}
		ft_memcpy(new_t, result->t, sizeof(double) * result->count);
		//ft_memcpy(new_object, result->object, sizeof(void *) * result->count);
		free(result->t);
		//free(result->object);
		result->t = new_t;
	//	result->object = new_object;
	}
    if (!result->t)
    {
        fprintf(stderr, "Error: Memory allocation failed in add_intersection\n");
        exit(1);
    }
	result->t[result->count] = t;
	//result->object[result->count] = cylinder;
	result->count++;
}

void intersect_caps(t_cylinder cylinder, t_ray ray, t_intersections *result)
{
	double t_min;
	double t_max;
	double origin_projection;
	double direction_projection;
	t_tuple axis_normal;

	axis_normal = tuple_normalize(cylinder.axis);
	origin_projection = tuple_dot(tuple_subtract(ray.origin, cylinder.center), axis_normal);
	direction_projection = tuple_dot(ray.direction, axis_normal);
	t_min = (cylinder.min - origin_projection) / direction_projection;
	t_max = (cylinder.max - origin_projection) / direction_projection;
	if (check_cap(ray, t_min, cylinder))
		add_intersection(result, t_min + EPSILON);
	if (check_cap(ray, t_max, cylinder))
		add_intersection(result, t_max + EPSILON);
}

void	calculate_t(double *t1, double *t2, double discriminant, double a, double b)
{
	if (fabs(a) < EPSILON)
	{
		*t1 = *t2 = INFINITY;  // Or handle it appropriately
		return;
	}
	*t1 = (-b - sqrt(discriminant)) / (2 * a);
	*t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (fabs(*t1 - *t2) > EPSILON && *t1 > *t2)
	{
		double temp = *t1;
		*t1 = *t2;
		*t2 = temp;
	}
}

void intersect_body(double a, double b, double c, t_intersections *result, t_cylinder cylinder, t_ray ray)	
{
	double	discriminant;
	double	t1;
	double	t2;
	double origin_projection;
	double direction_projection;
	double y1;
	double y2;

	discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
	{
		calculate_t(&t1, &t2, discriminant, a, b);// Dont forget to change this!!
		//tuple_dot(tuple_subtract(ray.origin, cylinder.center), axis_normal);
		origin_projection = tuple_dot(tuple_subtract(ray.origin, cylinder.center), cylinder.axis);
		direction_projection = tuple_dot(ray.direction, cylinder.axis);
		y1 = origin_projection + t1 * direction_projection;
		y2 = origin_projection + t2 * direction_projection;
	    if (y1 >= cylinder.min && y1 <= cylinder.max) {
        	add_intersection(result, t1);
		}
		if (y2 >= cylinder.min && y2 <= cylinder.max) {
			add_intersection(result, t2);
		}
	}
}

t_intersections	intersect_cylinder(t_cylinder cylinder, t_ray ray)
{
	t_intersections	result;
	t_tuple			oc;
	double			a;
	double			b;
	double			c;

	result.count = 0;
	result.t = NULL;
	result.object = NULL;
	oc = tuple_subtract(ray.origin, cylinder.center);
	a = tuple_dot(ray.direction, ray.direction) - pow(tuple_dot(ray.direction,
				cylinder.axis), 2);
	b = 2 * (tuple_dot(ray.direction, oc) - tuple_dot(ray.direction,
				cylinder.axis) * tuple_dot(oc, cylinder.axis));
	c = tuple_dot(oc, oc) - pow(tuple_dot(oc, cylinder.axis), 2)
		- pow (cylinder.diameter / 2, 2);
	intersect_body(a, b, c, &result, cylinder, ray);
	intersect_caps(cylinder, ray, &result);
	//printf(MAG"radius: %f\n"RESET, cylinder.diameter / 2);
	//printf("cylinder diameter: %f\n", cylinder.diameter);
	return (result);
}
