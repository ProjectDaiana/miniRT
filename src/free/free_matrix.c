/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:49:38 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 19:49:40 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_matrix(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (i < matrix->size)
	{
		free(matrix->m[i]);
		i++;
	}
	free(matrix->m);
}
