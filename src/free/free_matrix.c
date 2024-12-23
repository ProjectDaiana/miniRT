/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:49:38 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 17:44:22 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_mtrx(t_matrix *matrix)
{
	int i;

	i = 0;
	while (i < matrix->size)
	{
		free(matrix->m[i]);
		matrix->m[i] = NULL;
		i++;
	}
	free(matrix->m);
}