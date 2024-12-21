/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:49:47 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 20:42:56 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}


void	free_splits(char **split1, char **split2, char **split3)
{
	if (split1)
		ft_free_split(split1);
	if (split2)
		ft_free_split(split2);
	if (split3)
		ft_free_split(split3);
}
