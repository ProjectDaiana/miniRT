/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:23:42 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 20:23:43 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_matrix(t_matrix matrix, char *str, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf(YEL "%s\n" RESET, str);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			printf("%f ", matrix.m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
