/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:18:14 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 12:29:49 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	create_checkers_pattern(t_color c1, t_color c2)
{
	t_pattern	pattern;

	pattern.type = CHECKERS;
	pattern.color1 = c1;
	pattern.color2 = c2;
	pattern.transform.m = NULL;
	return (pattern);
}

t_color	pattern_at_checkers(t_pattern pattern, t_tuple point)
{
	double	scale;
	double	x;
	double	y;
	double	z;

	scale = 0.5;
	x = floor(point.x * scale + EPSILON);
	y = floor(point.y * scale + EPSILON);
	z = floor(point.z * scale + EPSILON);
	x = fabs(x);
	y = fabs(y);
	z = fabs(z);
	if (((int)x + (int)y + (int)z) % 2 == 0)
		return (pattern.color1);
	return (pattern.color2);
}

t_color	pattern_at(t_pattern pattern, t_tuple point)
{
	if (pattern.type == CHECKERS)
		return (pattern_at_checkers(pattern, point));
	return (create_color(0, 0, 0));
}

t_color	pattern_at_shape(t_pattern pattern, void *shape, t_tuple world_point)
{
	t_matrix	shape_inv;
	t_matrix	pattern_inv;
	t_tuple		object_point;
	t_tuple		pattern_point;
	t_color		result;

	result = create_color(0, 0, 0);
	if (!shape || !is_valid_tuple(world_point))
		return (result);
	shape_inv = inverse_matrix(&((t_plane *)shape)->transform);
	if (!shape_inv.m)
		return (result);
	pattern_inv = inverse_matrix(&pattern.transform);
	if (!pattern_inv.m)
	{
		free_mtrx(&shape_inv);
		return (result);
	}
	object_point = matrix_multiply_tuple(shape_inv, world_point);
	pattern_point = matrix_multiply_tuple(pattern_inv, object_point);
	free_mtrx(&shape_inv);
	free_mtrx(&pattern_inv);
	return (pattern_at(pattern, pattern_point));
}

void	free_pattern(t_pattern *pattern)
{
	if (!pattern)
		return ;
	if (pattern->transform.m)
		free_mtrx(&pattern->transform);
}
