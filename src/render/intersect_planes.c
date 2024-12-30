/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_planes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:35:16 by tasha             #+#    #+#             */
/*   Updated: 2024/12/30 12:28:55 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_plane_intersection_values(t_intersections *result, t_plane *plane,
		double t)
{
	result->count = 1;
	result->t = ft_calloc(1, sizeof(double));
	result->object = ft_calloc(1, sizeof(void *));
	if (!result->t || !result->object)
	{
		free_intersections(result);
		return ;
	}
	result->t[0] = t;
	result->object[0] = plane;
}

t_intersections	intersect_plane(t_plane *plane, t_ray ray)
{
	double			denom;
	t_tuple			p0l0;
	double			t;
	t_intersections	result;

	result.count = 0;
	result.t = NULL;
	result.object = NULL;
	denom = tuple_dot(plane->normal, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		p0l0 = tuple_subtract(plane->point, ray.origin);
		t = tuple_dot(p0l0, plane->normal) / denom;
		if (t >= 0)
			set_plane_intersection_values(&result, plane, t);
	}
	return (result);
}
