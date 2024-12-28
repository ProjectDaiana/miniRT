/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:19:49 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/28 16:05:36 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	intersect_caps(t_cylinder cylinder, t_ray ray, t_intersections *result)
// {
// 	double	t;
// 	double	direction_dot;

// 	direction_dot = tuple_dot(ray.direction, cylinder.axis);
// 	if (fabs(direction_dot) < EPSILON)
// 		return ;
// 	t = tuple_dot(tuple_subtract(tuple_add(cylinder.center,
// 					tuple_multiply(cylinder.axis, 0)), ray.origin),
// 			cylinder.axis) / direction_dot;
// 	if (check_cap(ray, t, cylinder))
// 		add_intersection(result, t);
// 	t = tuple_dot(tuple_subtract(tuple_add(cylinder.center,
// 					tuple_multiply(cylinder.axis, cylinder.height)),
// 				ray.origin), cylinder.axis) / direction_dot;
// 	if (check_cap(ray, t, cylinder))
// 		add_intersection(result, t);
// }

void	intersect_caps(t_cylinder *cylinder, t_ray ray, t_intersections *result)
{
	double	t;
	double	direction_dot;

	direction_dot = tuple_dot(ray.direction, cylinder->axis);
	if (fabs(direction_dot) < EPSILON)
		return ;

	t = tuple_dot(tuple_subtract(tuple_add(cylinder->center,
				tuple_multiply(cylinder->axis, -cylinder->height/2)), 
				ray.origin), cylinder->axis) / direction_dot;
	if (check_cap(ray, t, *cylinder))
		add_intersection(result, t, cylinder);

	t = tuple_dot(tuple_subtract(tuple_add(cylinder->center,
				tuple_multiply(cylinder->axis, cylinder->height/2)), 
				ray.origin), cylinder->axis) / direction_dot;
	if (check_cap(ray, t, *cylinder))
		add_intersection(result, t, cylinder);
}

// void	intersect_body(double a, double b, double c, t_intersections *result,
// 		t_cylinder cylinder, t_ray ray)
// {
// 	double	discriminant;
// 	double	t1;
// 	double	t2;
// 	double	y1;
// 	double	y2;
// 	t_tuple	p1;
// 	t_tuple	p2;

// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 		return ;
// 	calculate_t(&t1, &t2, discriminant, a, b);
// 	p1 = tuple_add(ray.origin, tuple_multiply(ray.direction, t1));
// 	p2 = tuple_add(ray.origin, tuple_multiply(ray.direction, t2));
// 	y1 = tuple_dot(tuple_subtract(p1, cylinder.center), cylinder.axis);
// 	y2 = tuple_dot(tuple_subtract(p2, cylinder.center), cylinder.axis);
// 	if (y1 >= 0 && y1 <= cylinder.height)
// 		add_intersection(result, t1);
// 	if (y2 >= 0 && y2 <= cylinder.height)
// 		add_intersection(result, t2);
// }


void	intersect_body(t_cylinder *cylinder, t_ray ray, t_intersections *result)
{
	double params[3] = {0, 0, 0};
	double disc;
	double t[2] = {INFINITY, INFINITY};
	double y[2] = {0, 0};
	t_tuple p1, p2;

	if (!cylinder || !result || !is_valid_tuple(ray.origin) || 
		!is_valid_tuple(ray.direction))
		return;

	calculate_cylinder_params(*cylinder, ray, params);
	disc = params[1] * params[1] - 4 * params[0] * params[2];
	
	if (disc < 0 || params[0] == 0)
		return;
	
	t[0] = (-params[1] - sqrt(disc)) / (2 * params[0]);
	t[1] = (-params[1] + sqrt(disc)) / (2 * params[0]);
	
	p1 = tuple_add(ray.origin, tuple_multiply(ray.direction, t[0]));
	p2 = tuple_add(ray.origin, tuple_multiply(ray.direction, t[1]));
	
	if (!is_valid_tuple(p1) || !is_valid_tuple(p2))
		return;

	y[0] = tuple_dot(tuple_subtract(p1, cylinder->center), cylinder->axis);
	y[1] = tuple_dot(tuple_subtract(p2, cylinder->center), cylinder->axis);
	
	check_cylinder_bounds(*cylinder, t, y);
	
	if (t[0] != INFINITY)
		add_intersection(result, t[0], cylinder);
	if (t[1] != INFINITY)
		add_intersection(result, t[1], cylinder);
}
