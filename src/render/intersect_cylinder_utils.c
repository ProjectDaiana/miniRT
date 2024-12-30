/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:15:28 by tasha             #+#    #+#             */
/*   Updated: 2024/12/30 12:28:40 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cylinder_intersection(t_intersections *result)
{
	result->count = 0;
	result->t1 = 0;
	result->t2 = 0;
}

void	calculate_cylinder_params(t_cylinder cylinder, t_ray ray,
		double *params)
{
	t_tuple	oc;

	if (!params || !is_valid_tuple(ray.origin) || !is_valid_tuple(ray.direction)
		|| !is_valid_tuple(cylinder.center) || !is_valid_tuple(cylinder.axis))
		return ;
	oc = tuple_subtract(ray.origin, cylinder.center);
	if (!is_valid_tuple(oc))
		return ;
	params[0] = tuple_dot(ray.direction, ray.direction)
		- pow(tuple_dot(ray.direction, cylinder.axis), 2);
	params[1] = 2 * (tuple_dot(ray.direction, oc) - tuple_dot(ray.direction,
				cylinder.axis) * tuple_dot(oc, cylinder.axis));
	params[2] = tuple_dot(oc, oc) - pow(tuple_dot(oc, cylinder.axis), 2)
		- pow(cylinder.diameter / 2, 2);
}

void	add_valid_intersection(t_intersections *result, double t,
		t_cylinder *cylinder, int *index)
{
	result->t[*index] = t;
	result->object[*index] = cylinder;
	(*index)++;
}
