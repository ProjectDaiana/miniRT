/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:11:50 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 13:22:13 by tasha            ###   ########.fr       */
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

void	init_world_intersection(t_intersections *result)
{
	result->count = 0;
	result->t1 = 0;
	result->t2 = 0;
	result->t = NULL;
	result->object = NULL;
	result->capacity = 0;
}

void	allocate_intersections(t_intersections *result, double *t,
		t_cylinder *cylinder)
{
	int	index;

	result->count = (t[0] != INFINITY) + (t[1] != INFINITY);
	if (result->count > 0)
	{
		result->t = ft_calloc(result->count, sizeof(double));
		result->object = ft_calloc(result->count, sizeof(void *));
		index = 0;
		if (t[0] != INFINITY)
			add_valid_intersection(result, t[0], cylinder, &index);
		if (t[1] != INFINITY)
			add_valid_intersection(result, t[1], cylinder, &index);
	}
}

void	reallocate_intersection_arrays(t_intersections *result)
{
	double	*new_t;
	void	**new_object;

	result->capacity *= 2;
	new_t = ft_calloc(result->capacity, sizeof(double));
	new_object = ft_calloc(result->capacity, sizeof(void *));
	if (!new_t || !new_object)
	{
		free(new_t);
		free(new_object);
		return ;
	}
	ft_memcpy(new_t, result->t, result->count * sizeof(double));
	ft_memcpy(new_object, result->object, result->count * sizeof(void *));
	free(result->t);
	free(result->object);
	result->t = new_t;
	result->object = new_object;
}
