/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:13:36 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 19:23:57 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_matrix	create_view_matrices(t_tuple forward, t_tuple left,
		t_tuple from)
{
	t_matrix	orientation;
	t_matrix	trans_matrix;
	t_matrix	result;

	orientation = create_matrix(4);
	if (!orientation.m)
		return (orientation);
	set_orientation_matrix(&orientation, left, tuple_cross(forward, left),
		forward);
	trans_matrix = translation(-from.x, -from.y, -from.z);
	if (!trans_matrix.m)
	{
		free_mtrx(&orientation);
		return (trans_matrix);
	}
	result = matrix_multiply(orientation, trans_matrix);
	free_mtrx(&orientation);
	free_mtrx(&trans_matrix);
	return (result);
}

t_matrix	look_at(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple	forward;
	t_tuple	left;

	forward = tuple_normalize(tuple_subtract(to, from));
	left = tuple_cross(tuple_normalize(up), forward);
	return (create_view_matrices(forward, left, from));
}
