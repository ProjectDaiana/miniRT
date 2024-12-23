/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:51:08 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 19:46:23 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	assign_matrix_3(t_matrix *matrix, double m[3][3])
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < matrix->size)
// 	{
// 		j = 0;
// 		while (j < matrix->size)
// 		{
// 			matrix->m[i][j] = m[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// }

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
	if (!matrix.m)
	{
		matrix.size = 0;
		return (matrix);
	}
	while (i < size)
	{
		matrix.m[i] = ft_calloc(size, sizeof(double));
		if (!matrix.m[i])
		{
			while (--i >= 0)
				free(matrix.m[i]);
			free(matrix.m);
			matrix.m = NULL;
			matrix.size = 0;
			return (matrix);
		}
		i++;
	}
	return (matrix);
}

// t_matrix	create_matrix_3(double m[3][3])
// {
// 	t_matrix	matrix;
// 	int			i;
// 	int			j;

// 	matrix = create_matrix(3);
// 	i = 0;
// 	while (i < 3)
// 	{
// 		j = 0;
// 		while (j < 3)
// 		{
// 			matrix.m[i][j] = m[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (matrix);
// }
