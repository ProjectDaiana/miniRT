/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:51:08 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 21:16:24 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	allocate_matrix_rows(t_matrix *matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		matrix->m[i] = ft_calloc(size, sizeof(double));
		if (!matrix->m[i])
		{
			while (--i >= 0)
				free(matrix->m[i]);
			free(matrix->m);
			matrix->m = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

t_matrix	create_matrix(int size)
{
	t_matrix	matrix;

	matrix.size = size;
	matrix.m = ft_calloc(size, sizeof(double *));
	if (!matrix.m)
	{
		matrix.size = 0;
		return (matrix);
	}
	if (!allocate_matrix_rows(&matrix, size))
	{
		matrix.size = 0;
		return (matrix);
	}
	return (matrix);
}
