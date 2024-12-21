/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:13:36 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 21:32:11 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	look_at(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		left;
	t_matrix	orientation;
	t_matrix	trans_matrix;

	forward = tuple_normalize(tuple_subtract(to, from));
	left = tuple_cross(tuple_normalize(up), forward);
	orientation = create_matrix(4);
	set_orientation_matrix(&orientation, left, tuple_cross(forward, left),
		forward);
	trans_matrix = translation(-from.x, -from.y, -from.z);
	return (matrix_multiply(orientation, trans_matrix));
}
