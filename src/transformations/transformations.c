/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:22:24 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/26 19:08:48 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	translation(double x, double y, double z)
{
	t_matrix	translation_matrix;

	translation_matrix = create_matrix(4);
	translation_matrix.m[0][0] = 1;
	translation_matrix.m[1][1] = 1;
	translation_matrix.m[2][2] = 1;
	translation_matrix.m[3][3] = 1;
	translation_matrix.m[0][3] = x;
	translation_matrix.m[1][3] = y;
	translation_matrix.m[2][3] = z;
	return (translation_matrix);
}

t_matrix	scaling(double x, double y, double z)
{
	t_matrix	scaling_matrix;

	scaling_matrix = create_matrix(4);
	scaling_matrix.m[0][0] = x;
	scaling_matrix.m[1][1] = y;
	scaling_matrix.m[2][2] = z;
	scaling_matrix.m[3][3] = 1;
	return (scaling_matrix);
}

static void	set_skew_matrix(t_matrix *matrix, t_skew_params params)
{
	matrix->m[0][0] = 1;
	matrix->m[0][1] = params.x_y;
	matrix->m[0][2] = params.x_z;
	matrix->m[1][0] = params.y_x;
	matrix->m[1][1] = 1;
	matrix->m[1][2] = params.y_z;
	matrix->m[2][0] = params.z_x;
	matrix->m[2][1] = params.z_y;
	matrix->m[2][2] = 1;
	matrix->m[3][3] = 1;
}

t_matrix	skewing(t_skew_params params)
{
	t_matrix	skew_matrix;

	skew_matrix = create_matrix(4);
	set_skew_matrix(&skew_matrix, params);
	return (skew_matrix);
}

t_tuple	transform_point(t_matrix transform, t_tuple point)
{
	t_tuple	result;

	result = matrix_multiply_tuple(transform, point);
	return (result);
}
