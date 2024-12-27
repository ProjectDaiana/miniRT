/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:36:39 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/24 15:50:51 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_base_color(t_material material, t_tuple point)
{
	t_color	default_color;

	default_color = create_color(0, 0, 0);
	if (!is_valid_tuple(point))
		return (default_color);
	if (material.color.r < 0 || material.color.g < 0 || material.color.b < 0)
		return (default_color);
	if (material.pattern.type == CHECKERS)
	{
		if (material.pattern.color1.r < 0 || material.pattern.color1.g < 0
			|| material.pattern.color1.b < 0 || material.pattern.color2.r < 0
			|| material.pattern.color2.g < 0 || material.pattern.color2.b < 0)
			return (default_color);
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

// int	init_plane_color(char **split, char ***color)
// {
// 	*color = ft_split(split[3], ',');
// 	if (!validate_coordinates(*color, "plane color", split))
// 	{
// 		ft_free_split(*color);
// 		return (0);
// 	}
// 	return (1);
// }

int	init_plane_color(char **split, char ***color)
{
	int		count;
	double	value;

	if (!split[3])
		return (0);
	*color = ft_split(split[3], ',');
	if (!*color)
		return (0);
	count = 0;
	while ((*color)[count])
		count++;
	if (count != 3)
	{
		ft_free_split(*color);
		*color = NULL;
		return (0);
	}
	for (int i = 0; i < 3; i++)
	{
		value = ft_atof((*color)[i]);
		if (value < 0 || value > 255)
		{
			ft_free_split(*color);
			*color = NULL;
			return (0);
		}
	}
	return (1);
}
