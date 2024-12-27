/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:49:38 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/26 20:12:29 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_mtrx(t_matrix *matrix)
{
	int i;

	if (!matrix || !matrix->m)
		return ;

	i = 0;
	while (i < matrix->size)
	{
		free(matrix->m[i]);
		matrix->m[i] = NULL;
		i++;
	}
	free(matrix->m);
}