/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_identity_matrix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:50:51 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/24 01:06:50 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	create_identity_matrix(void)
{
	t_matrix	matrix;
	int			i;
	int			j;

	ft_memset(&matrix, 0, sizeof(t_matrix));
	matrix.size = 4;
	matrix.m = malloc(sizeof(double *) * matrix.size);
	if (!matrix.m)
		return (matrix);
		
	i = 0;
	while (i < matrix.size)
	{
		matrix.m[i] = malloc(sizeof(double) * matrix.size);
		if (!matrix.m[i])
		{
			while (--i >= 0)
				free(matrix.m[i]);
			free(matrix.m);
			matrix.m = NULL;
			return (matrix);
		}
		j = 0;
		while (j < matrix.size)
		{
			matrix.m[i][j] = (i == j) ? 1.0 : 0.0;
			j++;
		}
		i++;
	}
	return (matrix);
}
