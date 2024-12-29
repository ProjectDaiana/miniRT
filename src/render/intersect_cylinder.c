/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:19:49 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 13:59:22 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_caps(t_cylinder *cylinder, t_ray ray, t_intersections *result)
{
	double	t;
	double	direction_dot;

	direction_dot = tuple_dot(ray.direction, cylinder->axis);
	if (fabs(direction_dot) < EPSILON)
		return ;
	// Bottom cap
	t = tuple_dot(tuple_subtract(tuple_add(cylinder->center,
					tuple_multiply(cylinder->axis, -cylinder->height / 2)),
				ray.origin), cylinder->axis) / direction_dot;
	if (check_cap(ray, t, *cylinder))
		add_intersection(result, t, cylinder);
	// Top cap
	t = tuple_dot(tuple_subtract(tuple_add(cylinder->center,
					tuple_multiply(cylinder->axis, cylinder->height / 2)),
				ray.origin), cylinder->axis) / direction_dot;
	if (check_cap(ray, t, *cylinder))
		add_intersection(result, t, cylinder);
}

void	calculate_intersection_points(t_ray ray, t_cylinder *cylinder,
		double *t, double *y)
{
	t_tuple	p1;
	t_tuple	p2;

	p1 = tuple_add(ray.origin, tuple_multiply(ray.direction, t[0]));
	p2 = tuple_add(ray.origin, tuple_multiply(ray.direction, t[1]));
	if (!is_valid_tuple(p1) || !is_valid_tuple(p2))
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
		return ;
	}
	y[0] = tuple_dot(tuple_subtract(p1, cylinder->center), cylinder->axis);
	y[1] = tuple_dot(tuple_subtract(p2, cylinder->center), cylinder->axis);
}

void	intersect_body(t_cylinder *cylinder, t_ray ray, t_intersections *result)
{
	double	params[3];
	double	t[2];
	double	y[2];

	ft_memset(params, 0, sizeof(params));
	ft_memset(y, 0, sizeof(y));
	t[0] = INFINITY;
	t[1] = INFINITY;
	if (!cylinder || !result || !is_valid_tuple(ray.origin)
		|| !is_valid_tuple(ray.direction))
		return ;
	calculate_cylinder_intersections(*cylinder, ray, t, y);
	if (t[0] != INFINITY || t[1] != INFINITY)
	{
		calculate_intersection_points(ray, cylinder, t, y);
		check_cylinder_bounds(*cylinder, t, y);
		if (t[0] != INFINITY)
			add_intersection(result, t[0], cylinder);
		if (t[1] != INFINITY)
			add_intersection(result, t[1], cylinder);
	}
}

t_intersections	intersect_cylinder(t_cylinder cylinder, t_ray ray)
{
	t_intersections	result;

	result.count = 0;
	result.capacity = 4;
	result.t = ft_calloc(result.capacity, sizeof(double));
	result.object = ft_calloc(result.capacity, sizeof(void *));
	if (!result.t || !result.object)
	{
		free_intersections(&result);
		result.capacity = 0;
		return (result);
	}
	intersect_body(&cylinder, ray, &result);
	intersect_caps(&cylinder, ray, &result);
	return (result);
}
