/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:53:24 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 21:19:41 by darotche         ###   ########.fr       */
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

void	parse_cylinder_properties(char **split, t_cylinder *cylinder)
{
	char	**pos;
	char	**orient;
	char	**color;

	pos = ft_split(split[1], ',');
	orient = ft_split(split[2], ',');
	cylinder->center = create_point(ft_atof(pos[0]), ft_atof(pos[1]),
			ft_atof(pos[2]));
	cylinder->axis = create_vector(ft_atof(orient[0]), ft_atof(orient[1]),
			ft_atof(orient[2]));
	cylinder->axis = tuple_normalize(cylinder->axis);
	cylinder->diameter = ft_atof(split[3]);
	cylinder->height = ft_atof(split[4]);
	color = ft_split(split[5], ',');
	cylinder->material.color = create_material_color(color);
	init_cylinder_material(cylinder);
	free_splits(NULL, pos, orient);
	ft_free_split(color);
}

int	validate_cylinder_properties(char **split)
{
	char	**pos;
	char	**orient;
	char	**color;
	int		valid;

	pos = ft_split(split[1], ',');
	orient = ft_split(split[2], ',');
	color = ft_split(split[5], ',');
	valid = validate_coordinates(pos, "cylinder position", split)
		&& validate_orient(orient, "cylinder orientation", split)
		&& validate_coordinates(color, "cylinder color", split);
	free_splits(NULL, pos, orient);
	ft_free_split(color);
	return (valid);
}

void	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	cylinder;
	char		**split;

	ft_memset(&cylinder, 0, sizeof(t_cylinder));
	split = ft_split(line, ' ');
	if (!validate_params(split, 5, "cylinder"))
		return ;
	parse_cylinder_properties(split, &cylinder);
	if (!validate_cylinder_properties(split))
	{
		free_splits(split, NULL, NULL);
		return ;
	}
	add_cylinder(scene, &cylinder);
	free_splits(split, NULL, NULL);
}
