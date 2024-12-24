/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:53:24 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 21:37:08 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	cylinder;
	char		**split;
	char		**pos;
	char		**orient;
	char		**color;

	ft_memset(&cylinder, 0, sizeof(t_cylinder));

	split = ft_split(line, ' ');
	if (!validate_params(split, 5, "cylinder"))
		return ;
	pos = ft_split(split[1], ',');
	orient = ft_split(split[2], ',');
	if (!validate_coordinates(pos, "cylinder position", split)
		|| !validate_coordinates(orient, "cylinder orientation", split))
	{
		free_splits(split, pos, orient);
		return ;
	}
	
	cylinder.center = create_point(ft_atof(pos[0]), ft_atof(pos[1]),
			ft_atof(pos[2]));
	cylinder.axis = create_vector(ft_atof(orient[0]), ft_atof(orient[1]),
			ft_atof(orient[2]));
	cylinder.axis = tuple_normalize(cylinder.axis);
	cylinder.diameter = ft_atof(split[3]);
	cylinder.height = ft_atof(split[4]);
	color = ft_split(split[5], ',');
	if (!validate_coordinates(color, "cylinder color", split))
	{
		free_splits(split, pos, orient);
		return ;
	}
	cylinder.material.color = create_material_color(color);
	init_cylinder_material(&cylinder);
	add_cylinder(scene, &cylinder);
	free_splits(split, pos, orient);
	ft_free_split(color);
}
