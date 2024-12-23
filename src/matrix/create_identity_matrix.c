/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_identity_matrix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:50:51 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 18:03:46 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	create_identity_matrix(void)
{
	t_matrix	matrix;
	int			i;
	int			j;

	matrix.size = 4;
	matrix.m = ft_calloc(matrix.size, sizeof(double *));
	i = 0;
	while (i < matrix.size)
	{
		matrix.m[i] = ft_calloc(matrix.size, sizeof(double));
		j = 0;
		while (j < matrix.size)
		{
			if (i == j)
				matrix.m[i][j] = 1.0;
			else
				matrix.m[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (matrix);
}
