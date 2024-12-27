/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:15:03 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/27 18:23:02 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_cap(t_ray ray, double t, t_cylinder cylinder)
{
	t_tuple	point;
	t_tuple	to_point;
	double	distance_from_axis;

	point = tuple_add(ray.origin, tuple_multiply(ray.direction, t));
	to_point = tuple_subtract(point, cylinder.center);
	distance_from_axis = sqrt(tuple_dot(to_point, to_point)
			- pow(tuple_dot(to_point, cylinder.axis), 2));
	return (distance_from_axis <= cylinder.diameter / 2);
}
