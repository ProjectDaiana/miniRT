/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:18:10 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 19:00:04 by tasha            ###   ########.fr       */
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
	// Initialize all variables
	t_tuple normal = create_vector(0, 0, 0);
	t_tuple obj_point;
	t_tuple axis_projection;
	t_tuple radial_vector;
	double projection_len = 0.0;

	if (!cylinder || !is_valid_tuple(world_point) || 
		!is_valid_tuple(cylinder->center) || !is_valid_tuple(cylinder->axis))
		return normal;

	if (fabs(tuple_magnitude(cylinder->axis) - 1.0) > EPSILON)
		cylinder->axis = tuple_normalize(cylinder->axis);

	obj_point = tuple_subtract(world_point, cylinder->center);
	if (!is_valid_tuple(obj_point))
		return create_vector(0, 1, 0);

	projection_len = tuple_dot(obj_point, cylinder->axis);
	axis_projection = tuple_multiply(cylinder->axis, projection_len);
	if (!is_valid_tuple(axis_projection))
		return create_vector(0, 1, 0);

	radial_vector = tuple_subtract(obj_point, axis_projection);
	if (!is_valid_tuple(radial_vector))
		return create_vector(0, 1, 0);

	normal = tuple_normalize(radial_vector);
	if (!is_valid_tuple(normal))
		return create_vector(0, 1, 0);

	return normal;
}
