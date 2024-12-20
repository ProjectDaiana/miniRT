/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:18:10 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 21:38:31 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	normal_at_cylinder(t_cylinder *cylinder, t_tuple world_point)
{
	t_tuple	obj_point;
	t_tuple	axis_projection;
	t_tuple	radial_vect;
	double	projection_len;
	t_tuple	normal;

	obj_point = tuple_subtract(world_point, cylinder->center);
	projection_len = tuple_dot(obj_point, cylinder->axis);
	if (projection_len >= cylinder->height - EPSILON)
	{
		normal = cylinder->axis;
		return (normal);
	}
	if (projection_len <= EPSILON)
	{
		normal = tuple_negate(cylinder->axis);
		return (normal);
	}
	axis_projection = tuple_multiply(cylinder->axis, projection_len);
	radial_vect = tuple_subtract(obj_point, axis_projection);
	normal = tuple_normalize(radial_vect);
	return (normal);
}
