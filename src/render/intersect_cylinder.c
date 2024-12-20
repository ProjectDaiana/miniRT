/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:19:49 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 21:20:09 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_caps(t_cylinder cylinder, t_ray ray, t_intersections *result)
{
	double	t;
	double	direction_dot;

	direction_dot = tuple_dot(ray.direction, cylinder.axis);
	if (fabs(direction_dot) < EPSILON)
		return ;
	t = tuple_dot(tuple_subtract(tuple_add(cylinder.center,
					tuple_multiply(cylinder.axis, 0)), ray.origin),
			cylinder.axis) / direction_dot;
	if (check_cap(ray, t, cylinder))
		add_intersection(result, t);
	t = tuple_dot(tuple_subtract(tuple_add(cylinder.center,
					tuple_multiply(cylinder.axis, cylinder.height)),
				ray.origin), cylinder.axis) / direction_dot;
	if (check_cap(ray, t, cylinder))
		add_intersection(result, t);
}

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
	p1 = tuple_add(ray.origin, tuple_multiply(ray.direction, t1));
	p2 = tuple_add(ray.origin, tuple_multiply(ray.direction, t2));
	y1 = tuple_dot(tuple_subtract(p1, cylinder.center), cylinder.axis);
	y2 = tuple_dot(tuple_subtract(p2, cylinder.center), cylinder.axis);
	if (y1 >= 0 && y1 <= cylinder.height)
		add_intersection(result, t1);
	if (y2 >= 0 && y2 <= cylinder.height)
		add_intersection(result, t2);
}
