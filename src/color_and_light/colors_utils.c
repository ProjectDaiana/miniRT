/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:36:39 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 20:52:15 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_color	get_base_color(t_material material, t_tuple point)
{
	if (material.pattern.type == CHECKERS)
	{
		return (pattern_at(material.pattern, point));
	}
	return (material.color);
}

t_color	create_material_color(char **color_values)
{
	return (create_color(ft_atof(color_values[0]) / 255.0,
			ft_atof(color_values[1]) / 255.0, ft_atof(color_values[2])
			/ 255.0));
}

void	set_color_components(t_color *dest, char **color_values)
{
	dest->r = ft_atof(color_values[0]);
	dest->g = ft_atof(color_values[1]);
	dest->b = ft_atof(color_values[2]);
}

int	init_plane_color(char **split, char ***color)
{
	*color = ft_split(split[3], ',');
	if (!validate_coordinates(*color, "plane color", split))
	{
		ft_free_split(*color);
		return (0);
	}
	return (1);
}
