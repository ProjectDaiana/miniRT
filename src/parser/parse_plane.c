/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:50:31 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 19:25:53 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_plane(char *line, t_scene *scene)
{
	t_plane	plane;
	char	**split = NULL;
	char	**pos = NULL;
	char	**normal = NULL;
	char	**color = NULL;
	int		param_count = 0;

	if (!init_plane_splits(line, &split, &pos, &normal))
		return;
	
	while (split[param_count])
		param_count++;
	
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
	if (color)
		ft_free_split(color);
}
