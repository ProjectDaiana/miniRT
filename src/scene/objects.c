/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:18:02 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 20:33:16 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_plane_pattern(t_plane *plane)
{
	// t_color		white;
	t_color		black;
	t_matrix	scale;
	t_color base_color;

	// white = create_color(1.0, 1.0, 1.0);
	black = create_color(0.0, 0.0, 0.0);
	base_color = plane->material.color;
	plane->material.pattern = create_checkers_pattern(base_color, black);
	scale = scaling(2, 2, 2);
	plane->material.pattern.transform = scale;
}

t_plane	create_plane(t_tuple point, t_tuple normal, t_color color)
{
	t_plane	plane;

	ft_memset(&plane, 0, sizeof(t_plane));

	plane.point = point;
	plane.normal = tuple_normalize(normal);
	plane.transform = create_identity_matrix();
	init_plane_material(&plane, color);
	// set_plane_pattern(&plane);
	return (plane);
}
