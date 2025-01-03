/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:18:02 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 12:29:45 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_plane_pattern(t_plane *plane)
{
	t_color		black;
	t_matrix	scale;
	t_color		base_color;

	base_color = plane->material.color;
	if (plane->material.pattern.transform.m)
		free_mtrx(&plane->material.pattern.transform);
	if (plane->material.pattern.type == CHECKERS)
	{
		black = create_color(0.0, 0.0, 0.0);
		plane->material.pattern = create_checkers_pattern(base_color, black);
	}
	else
	{
		plane->material.pattern.type = SOLID;
		plane->material.pattern.color1 = base_color;
	}
	scale = scaling(1, 1, 1);
	plane->material.pattern.transform = scale;
}

t_plane	create_plane(t_tuple point, t_tuple normal, t_color color)
{
	t_plane		plane;
	t_matrix	transform;

	ft_memset(&plane, 0, sizeof(t_plane));
	plane.point = point;
	plane.normal = tuple_normalize(normal);
	transform = create_identity_matrix();
	if (!transform.m)
	{
		return (plane);
	}
	plane.transform = transform;
	init_plane_material(&plane, color);
	return (plane);
}
