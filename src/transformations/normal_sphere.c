/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:26:36 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 21:27:34 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_tuple	normal_at_sphere(t_sphere *sphere, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;

	object_point = tuple_subtract(world_point, sphere->center);
	object_normal = tuple_normalize(object_point);
	if (tuple_dot(object_normal, tuple_subtract(world_point,
				sphere->center)) < 0)
		object_normal = tuple_negate(object_normal);
	return (object_normal);
}
