/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_identity_matrix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:50:51 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 21:09:47 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	initialize_matrix(int size)
{
	t_matrix	matrix;
	int			i;

	ft_memset(&matrix, 0, sizeof(t_matrix));
	matrix.size = size;
	matrix.m = ft_calloc(matrix.size, sizeof(double *));
	if (!matrix.m)
		return (matrix);
	i = 0;
	while (i < matrix.size)
	{
		matrix.m[i] = ft_calloc(matrix.size, sizeof(double));
		if (!matrix.m[i])
		{
			while (--i >= 0)
				free(matrix.m[i]);
			free(matrix.m);
			matrix.m = NULL;
			return (matrix);
		}
		i++;
	}
	return (matrix);
}

void	fill_identity_matrix(t_matrix *matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < matrix->size)
	{
		j = 0;
		while (j < matrix->size)
		{
			if (i == j)
				matrix->m[i][j] = 1.0;
			else
				matrix->m[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

t_matrix	create_identity_matrix(void)
{
	t_matrix	matrix;

	matrix = initialize_matrix(4);
	if (matrix.m)
		fill_identity_matrix(&matrix);
	return (matrix);
}
