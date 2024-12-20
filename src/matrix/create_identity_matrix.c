/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_identity_matrix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:50:51 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 19:50:52 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	create_identity_matrix(void)
{
	t_matrix	matrix;
	int			i;
	int			j;

	matrix.size = 4;
	matrix.m = malloc(sizeof(double *) * matrix.size);
	i = 0;
	while (i < matrix.size)
	{
		matrix.m[i] = malloc(sizeof(double) * matrix.size);
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
