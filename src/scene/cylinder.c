#include "minirt.h"

// t_tuple	normal_at_cylinder(t_cylinder cylinder, t_tuple world_point)
// {
//     t_tuple obj_p;
//     t_tuple obj_n;
//     double dist;

//     obj_p = tuple_subtract(world_point, cylinder.center);
// //    dist = obj_p.x * obj_p.x + obj_p.z * obj_p.z; // For Y-axis aligned cylinder
//     // Check which axis the cylinder is aligned with to compute the distance correctly
//     if (cylinder.axis.y == 1) // Y-axis aligned
//         dist = obj_p.x * obj_p.x + obj_p.z * obj_p.z;
//     else if (cylinder.axis.x == 1) // X-axis aligned
//         dist = obj_p.y * obj_p.y + obj_p.z * obj_p.z;
//     else if (cylinder.axis.z == 1) // Z-axis aligned
//         dist = obj_p.x * obj_p.x + obj_p.y * obj_p.y;
// 	else
// 		return (create_vector(0, 0, 0));
//     if (dist < pow(cylinder.diameter / 2, 2))
//     {
//         // Handle normals for caps
//         if (cylinder.axis.y == 1.0)
//         {
//             if (obj_p.y >= cylinder.max)
//                 return (create_vector(0, 1, 0)); // Top cap normal
//             if (obj_p.y <= cylinder.min)
//                 return (create_vector(0, -1, 0)); // Bottom cap normal
//         }
//         else if (cylinder.axis.x == 1.0)
//         {
//             if (obj_p.x >= cylinder.max)
//                 return (create_vector(1, 0, 0)); // Top cap normal (X-axis)
//             if (obj_p.x <= cylinder.min)
//                 return (create_vector(-1, 0, 0)); // Bottom cap normal (X-axis)
//         }
// else if (cylinder.axis.x == 1.0)
//         {
//             if (obj_p.z >= cylinder.max)
//                 return (create_vector(0, 0, 1)); // Top cap normal (Z-axis)
//             if (obj_p.z <= cylinder.min)
//                 return (create_vector(0, 0, -1)); // Bottom cap normal (Z-axis)
//         }
//     }

//     // For the body of the cylinder, calculate the normal based on the axis
//     if (cylinder.axis.y == 1)
//         obj_n = create_vector(obj_p.x, 0, obj_p.z); // Y-axis aligned
//     else if (cylinder.axis.x == 1)
//         obj_n = create_vector(0, obj_p.y, obj_p.z); // X-axis aligned
//     else if (cylinder.axis.z == 1)
//         obj_n = create_vector(obj_p.x, obj_p.y, 0); // Z-axis aligned
// 	else 
// 		return (create_vector(0, 0, 0));
//     return tuple_normalize(obj_n);
// }

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
// Caps in Y axis
// int check_cap(t_ray ray, double t, t_cylinder cylinder)
// {
// 	t_tuple	point;
// 	double	distance_from_axis;
// 	double	radius;

// 	radius = cylinder.diameter / 2;
// 	//printf("cylinder diameter: %f\n", cylinder.diameter);
// 	//printf(MAG"radius_squared: %f\n"RESET, radius * radius); // WARNING! Radius here and in intersect_cylinders differ 
//     point = tuple_add(ray.origin, tuple_multiply(ray.direction, t));
//     // Compute the distance from the cylinder's axis (which is the center of the cap)
// 	if (cylinder.axis.y == 1)
// 		distance_from_axis = pow(point.x - cylinder.center.x, 2) + pow(point.z - cylinder.center.z, 2);
// 	else if (cylinder.axis.x == 1)
// 		distance_from_axis = pow(point.y - cylinder.center.y, 2) + pow(point.z - cylinder.center.z, 2);
// 	else if (cylinder.axis.z == 1)
// 		distance_from_axis = pow(point.x - cylinder.center.x, 2) + pow(point.y - cylinder.center.y, 2);
// 	else
// 		return (0);
//     // If the distance from the axis is less than or equal to the radius squared, it's within the cap
//     return (distance_from_axis <= pow(radius,2));
// }


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

// void intersect_caps(t_cylinder cylinder, t_ray ray, t_intersections *result)
// {
// 	double	t_min;
// 	double	t_max;

// 	//ray.direction = tuple_normalize(ray.direction);

// 	if (cylinder.axis.x == 1.0)
// 	{
// 		t_min = (cylinder.min - ray.origin.x) / ray.direction.x;
// 		t_max = (cylinder.max - ray.origin.x) / ray.direction.x;
// 	}
// 	else if (cylinder.axis.y == 1.0)
// 	{
// 		t_min = (cylinder.min - ray.origin.y) / ray.direction.y;
// 		t_max = (cylinder.max - ray.origin.y) / ray.direction.y;
// 	}
// 	else if (cylinder.axis.z == 1.0)
// 	{
// 		t_min = (cylinder.min - ray.origin.z) / ray.direction.z;
// 		t_max = (cylinder.max - ray.origin.z) / ray.direction.z;
// 	}
// 	else
// 		return ;
//     if (check_cap(ray, t_min, cylinder))
// 	{
//         result->count++;
// 		//result->t = ft_calloc(sizeof(double), result->count);
// 		//result->object = ft_calloc(sizeof(void *), result->count);
// 		if (result->count == 1)
// 		{
// 			result->t = malloc(sizeof(double) * result->count);
// 			result->object = malloc(sizeof(void *) * result->count);
// 		}
// 		else
// 		{
//         	result->t = realloc(result->t, sizeof(double) * result->count);
//     		result->object = realloc(result->object, sizeof(void *) * result->count);
// 		}
// 		result->t[result->count - 1] = t_min;
//         result->object[result->count - 1] = &cylinder;
//     }
//     if (check_cap(ray, t_max, cylinder))
// 	{
//         result->count++;
// 		//result->t = ft_calloc(sizeof(double), result->count);
// 		//result->object = ft_calloc(sizeof(void *), result->count);
// 		if (result->count == 1)
// 		{
// 			result->t = malloc(sizeof(double) * result->count);
// 			result->object = malloc(sizeof(void *) * result->count);
// 		}
// 		else
// 		{
// 			result->t = realloc(result->t, sizeof(double) * result->count);
// 			result->object = realloc(result->object, sizeof(void *) * result->count);
// 		}
//         result->t[result->count - 1] = t_max;
//         result->object[result->count - 1] = &cylinder;
//     }
// }

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
	{
		result->count++;
		if (result->count == 1)
		{
			result->t = malloc(sizeof(double) * result->count);
			result->object = malloc(sizeof(void *) * result->count);
		}
		else
		{
			result->t = realloc(result->t, sizeof(double) * result->count);
			result->object = realloc(result->object, sizeof(void *) * result->count);
		}
		result->t[result->count - 1] = t_min;
		result->object[result->count - 1] = &cylinder;
	}
	if (check_cap(ray, t_max, cylinder))
	{
		result->count++;
		if (result->count == 1)
		{
			result->t = malloc(sizeof(double) * result->count);
			result->object = malloc(sizeof(void *) * result->count);
		}
		else
		{
			result->t = realloc(result->t, sizeof(double) * result->count);
			result->object = realloc(result->object, sizeof(void *) * result->count);
		}
		result->t[result->count - 1] = t_max;
		result->object[result->count - 1] = &cylinder;
	}

}

void	calculate_t(double *t1, double *t2, double discriminant, double a, double b)
{
	if (fabs(a) < EPSILON)
	{
		*t1 = *t2 = INFINITY;  // Or handle it appropriately
		return;
	}
	if (discriminant < 0)
    {
        *t1 = *t2 = INFINITY;  // No intersections
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
		calculate_t(&t1, &t2, discriminant, a, b);
		origin_projection = tuple_dot(ray.origin, cylinder.axis);
		direction_projection = tuple_dot(ray.direction, cylinder.axis);
		y1 = origin_projection + t1 * direction_projection;
		y2 = origin_projection + t2 * direction_projection;
		if (y1 < cylinder.min - EPSILON || y1 > cylinder.max)
			t1 = INFINITY;
		if (y2 < cylinder.min - EPSILON || y2 > cylinder.max)
			t2 = INFINITY;
		result->count = (t1 != INFINITY) + (t2 != INFINITY);
		result->t = malloc(sizeof(double) * result->count);
		result->object = malloc(sizeof(void *) * result->count);
		if (t1 != INFINITY)
		{
			result->t[0] = t1;
			result->object[0] = &cylinder;
		}
		if (t2 != INFINITY)
		{
			result->t[1] = t2;
			result->object[1] = &cylinder;
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
	result.t1 = 0;
	result.t2 = 0;
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
