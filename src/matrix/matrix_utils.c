/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:51:08 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 17:37:27 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	assign_matrix(t_matrix *matrix, double m[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < matrix->size)
	{
		j = 0;
		while (j < matrix->size)
		{
			matrix->m[i][j] = m[i][j];
			j++;
		}
		i++;
	}
}

t_matrix	create_matrix(int size)
{
	int			i;
	t_matrix	matrix;

	i = 0;
	matrix.size = size;
	matrix.m = ft_calloc(size, sizeof(double *));
	while (i < size)
	{
		matrix.m[i] = ft_calloc(size, sizeof(double));
		i++;
	}
	return (matrix);
}
