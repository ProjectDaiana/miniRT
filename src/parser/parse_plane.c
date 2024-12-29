/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:50:31 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 21:28:08 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_plane_material(t_plane *plane, char **split)
{
	int	param_count;

	param_count = 0;
	while (split[param_count])
		param_count++;
	if (param_count > 4)
		plane->material.reflective = ft_atof(split[4]);
	if (param_count > 5)
		plane->material.transparency = ft_atof(split[5]);
}

void	parse_plane(char *line, t_scene *scene)
{
	t_plane	plane;
	char	**split;
	char	**pos;
	char	**normal;
	char	**color;

	split = NULL;
	pos = NULL;
	normal = NULL;
	color = NULL;
	if (!init_plane_splits(line, &split, &pos, &normal))
		return ;
	if (!init_plane_color(split, &color))
	{
		free_splits(split, pos, normal);
		return ;
	}
	plane = create_plane_from_params(pos, normal, color);
	set_plane_material(&plane, split);
	add_plane(scene, &plane);
	free_splits(split, pos, normal);
	if (color)
		ft_free_split(color);
}
