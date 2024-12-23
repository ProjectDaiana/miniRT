/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:50:31 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 13:56:29 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_plane(char *line, t_scene *scene)
{
	t_plane	plane;
	char	**split;
	char	**pos;
	char	**normal;
	char	**color;
	int		param_count;

	split = ft_split(line, ' ');
	if (!split)
		return;
	
	param_count = 0;
	while (split[param_count])
		param_count++;
	
	if (!init_plane_splits(line, &split, &pos, &normal))
	{
		ft_free_split(split);
		return;
	}
	
	if (!init_plane_color(split, &color))
	{
		free_splits(split, pos, normal);
		return;
	}
	
	plane = create_plane_from_params(pos, normal, color);
	if (param_count > 4)
		plane.material.reflective = ft_atof(split[4]);
	if (param_count > 5)
		plane.material.transparency = ft_atof(split[5]);
	
	add_plane(scene, &plane);
	free_splits(split, pos, normal);
	ft_free_split(color);
}
