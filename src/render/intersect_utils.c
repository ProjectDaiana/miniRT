/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:11:50 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/27 17:37:38 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sort_intersections(t_intersections *xs)
{
	double	temp_t;
	void	*temp_obj;
	int		i;
	int		j;

	i = 0;
	while (i < xs->count - 1)
	{
		j = 0;
		while (j < xs->count - i - 1)
		{
			if (xs->t[j] > xs->t[j + 1])
			{
				temp_t = xs->t[j];
				xs->t[j] = xs->t[j + 1];
				xs->t[j + 1] = temp_t;
				temp_obj = xs->object[j];
				xs->object[j] = xs->object[j + 1];
				xs->object[j + 1] = temp_obj;
			}
			j++;
		}
		i++;
	}
}
