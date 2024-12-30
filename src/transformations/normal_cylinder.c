/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:18:10 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 12:30:20 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	validate_cylinder_inputs(t_cylinder *cylinder, t_tuple world_point)
{
	if (!cylinder || !is_valid_tuple(world_point)
		|| !is_valid_tuple(cylinder->center) || !is_valid_tuple(cylinder->axis))
		return (0);
	if (fabs(tuple_magnitude(cylinder->axis) - 1.0) > EPSILON)
		cylinder->axis = tuple_normalize(cylinder->axis);
	return (1);
}

static t_tuple	calculate_radial_vector(t_tuple obj_point, t_tuple axis,
		double *projection_len)
{
	t_tuple	axis_projection;
	t_tuple	radial_vector;

	*projection_len = tuple_dot(obj_point, axis);
	axis_projection = tuple_multiply(axis, *projection_len);
	if (!is_valid_tuple(axis_projection))
		return (create_vector(0, 1, 0));
	radial_vector = tuple_subtract(obj_point, axis_projection);
	if (!is_valid_tuple(radial_vector))
		return (create_vector(0, 1, 0));
	return (radial_vector);
}

t_tuple	normal_at_cylinder(t_cylinder *cylinder, t_tuple world_point)
{
	t_tuple	normal;
	t_tuple	obj_point;
	t_tuple	radial_vector;
	double	projection_len;

	if (!validate_cylinder_inputs(cylinder, world_point))
		return (create_vector(0, 0, 0));
	obj_point = tuple_subtract(world_point, cylinder->center);
	if (!is_valid_tuple(obj_point))
		return (create_vector(0, 1, 0));
	radial_vector = calculate_radial_vector(obj_point, cylinder->axis,
			&projection_len);
	normal = tuple_normalize(radial_vector);
	if (!is_valid_tuple(normal))
		return (create_vector(0, 1, 0));
	return (normal);
}
