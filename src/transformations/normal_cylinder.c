/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:18:10 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 15:38:02 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_tuple	normal_at_cylinder(t_cylinder *cylinder, t_tuple world_point)
// {
// 	t_tuple	obj_point;
// 	t_tuple	axis_projection;
// 	t_tuple	radial_vect;
// 	double	projection_len;
// 	t_tuple	normal;

// 	obj_point = tuple_subtract(world_point, cylinder->center);
// 	projection_len = tuple_dot(obj_point, cylinder->axis);
// 	if (projection_len >= cylinder->height - EPSILON)
// 	{
// 		normal = cylinder->axis;
// 		return (normal);
// 	}
// 	if (projection_len <= EPSILON)
// 	{
// 		normal = tuple_negate(cylinder->axis);
// 		return (normal);
// 	}
// 	axis_projection = tuple_multiply(cylinder->axis, projection_len);
// 	radial_vect = tuple_subtract(obj_point, axis_projection);
// 	normal = tuple_normalize(radial_vect);
// 	return (normal);
// }

t_tuple	normal_at_cylinder(t_cylinder *cylinder, t_tuple world_point)
{
	t_tuple	obj_point;
	t_tuple	axis_projection;
	t_tuple	radial_vect;
	double	projection_len;

	if (!cylinder)
		return (create_vector(0, 0, 0));
	if (fabs(tuple_magnitude(cylinder->axis) - 1.0) > EPSILON)
		return (create_vector(0, 1, 0));
	obj_point = tuple_subtract(world_point, cylinder->center);
	if (tuple_magnitude(obj_point) < EPSILON)
		return cylinder->axis;
	projection_len = tuple_dot(obj_point, cylinder->axis);
	if (projection_len >= cylinder->height/2 - EPSILON)
		return (cylinder->axis);
	if (projection_len <= -cylinder->height/2 + EPSILON)
		return (tuple_negate(cylinder->axis));
	axis_projection = tuple_multiply(cylinder->axis, projection_len);
	radial_vect = tuple_subtract(obj_point, axis_projection);
	if (tuple_magnitude(radial_vect) < EPSILON)
		return (cylinder->axis);
	return (tuple_normalize(radial_vect));
}
