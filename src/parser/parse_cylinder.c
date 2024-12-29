/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:53:24 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/28 23:51:58 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_orient(char **orient, char *element, char **to_free)
{
	if (!orient || !orient[0] || !orient[1] || !orient[2])
	{
		fprintf(stderr, "Error: Invalid %s position format\n", element);
		ft_free_split(to_free);
		return (0);
	}
	else if (ft_atof(orient[0]) == 0 && ft_atof(orient[1]) == 0
		&& ft_atof(orient[2]) == 0)
	{
		fprintf(stderr, "Error: Cylinder orientation cannot be (0,0,0)\n");
		ft_free_split(to_free);
		exit (0);
	}
	return (1);
}

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
	cylinder.center = create_point(ft_atof(pos[0]), ft_atof(pos[1]),
			ft_atof(pos[2]));
	cylinder.axis = create_vector(ft_atof(orient[0]), ft_atof(orient[1]),
			ft_atof(orient[2]));
    // if (tuple_magnitude(cylinder.axis) == 0.0)
    // {
    //     fprintf(stderr, "Error: Cylinder orientation cannot be (0,0,0)\n");
    //     free_splits(split, pos, orient);
    //     exit (0);
    // }		
	cylinder.axis = tuple_normalize(cylinder.axis);
	cylinder.diameter = ft_atof(split[3]);
	cylinder.height = ft_atof(split[4]);
	color = ft_split(split[5], ',');
	if (!validate_coordinates(pos, "cylinder position", split)
		|| !validate_orient(orient, "cylinder orientation", split)
		|| !validate_coordinates(color, "cylinder color", split))
	{
		free_splits(split, pos, orient);
		return ;
	}
	// if (!validate_coordinates(color, "cylinder color", split))
	// {
	// 	free_splits(split, pos, orient);
	// 	return ;
	// }
	init_cylinder_material(&cylinder);
	cylinder.material.color = create_material_color(color);
	cylinder.material.reflective = 0.3;
	add_cylinder(scene, &cylinder);
	free_splits(split, pos, orient);
	ft_free_split(color);
}
