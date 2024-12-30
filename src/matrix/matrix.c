/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:51:13 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 12:27:50 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	fill_row(t_matrix *submatrix, t_matrix *matrix, int row,
		t_submatrix_data *data)
{
	int	j;
	int	sub_j;

	j = 0;
	sub_j = 0;
	while (j < matrix->size)
	{
		if (j != data->col)
		{
			submatrix->m[data->sub_i][sub_j] = matrix->m[row][j];
			sub_j++;
		}
		j++;
	}
}

static void	fill_submatrix(t_matrix *submatrix, t_matrix *matrix, int row,
		int col)
{
	int					i;
	int					sub_i;
	t_submatrix_data	data;

	i = 0;
	sub_i = 0;
	data.col = col;
	while (i < matrix->size)
	{
		if (i != row)
		{
			data.sub_i = sub_i;
			fill_row(submatrix, matrix, i, &data);
			sub_i++;
		}
		i++;
	}
}

t_matrix	find_submatrix(t_matrix *matrix, int row, int col, int mtrx_size)
{
	t_matrix	submatrix;

	submatrix = create_matrix(mtrx_size - 1);
	fill_submatrix(&submatrix, matrix, row, col);
	return (submatrix);
}

t_tuple	matrix_multiply_tuple(t_matrix m, t_tuple t)
{
	t_tuple	result;

	result.x = m.m[0][0] * t.x + m.m[0][1] * t.y + m.m[0][2] * t.z + m.m[0][3]
		* t.w;
	result.y = m.m[1][0] * t.x + m.m[1][1] * t.y + m.m[1][2] * t.z + m.m[1][3]
		* t.w;
	result.z = m.m[2][0] * t.x + m.m[2][1] * t.y + m.m[2][2] * t.z + m.m[2][3]
		* t.w;
	result.w = m.m[3][0] * t.x + m.m[3][1] * t.y + m.m[3][2] * t.z + m.m[3][3]
		* t.w;
	return (result);
}

void	set_orientation_matrix(t_matrix *matrix, t_tuple left, t_tuple true_up,
		t_tuple forward)
{
	if (!matrix || !matrix->m)
		return ;
	matrix->m[0][0] = left.x;
	matrix->m[0][1] = left.y;
	matrix->m[0][2] = left.z;
	matrix->m[0][3] = 0;
	matrix->m[1][0] = true_up.x;
	matrix->m[1][1] = true_up.y;
	matrix->m[1][2] = true_up.z;
	matrix->m[1][3] = 0;
	matrix->m[2][0] = -forward.x;
	matrix->m[2][1] = -forward.y;
	matrix->m[2][2] = -forward.z;
	matrix->m[2][3] = 0;
	matrix->m[3][0] = 0;
	matrix->m[3][1] = 0;
	matrix->m[3][2] = 0;
	matrix->m[3][3] = 1;
}
