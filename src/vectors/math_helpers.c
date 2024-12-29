/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:24:58 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 20:42:33 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_compu	prepare_computations(double t, t_ray ray, t_intersections *xs)
{
	t_compu	comps;

	ft_memset(&comps, 0, sizeof(t_compu));
	if (!xs || !xs->object || !xs->t)
		return (comps);
	if (!xs->object[0])
		return (comps);
	comps.t = t;
	comps.object = xs->object[0];
	comps.point = position(ray, t);
	comps.eyev = tuple_negate(ray.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	if (tuple_magnitude(comps.normalv) < EPSILON)
		return (comps);
	if (tuple_dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = 1;
		comps.normalv = tuple_negate(comps.normalv);
	}
	else
		comps.inside = 0;
	comps.over_point = tuple_add(comps.point, tuple_multiply(comps.normalv,
				EPSILON));
	comps.reflectv = tuple_reflect(ray.direction, comps.normalv);
	return (comps);
}
