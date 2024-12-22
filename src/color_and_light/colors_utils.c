/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:36:39 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/22 22:16:48 by tbella-n         ###   ########.fr       */
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


int init_plane_color(char **split, char ***color)
{
    int     count;
    double  value;
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
        return (0);
    }
	//printf("Raw color values: %s %s %s\n", (*color)[0], (*color)[1], (*color)[2]);
    for (int i = 0; i < 3; i++)
    {
        value = ft_atof((*color)[i]);
        if (value < 0 || value > 255)
        {
            ft_free_split(*color);
            return (0);
        }
    }
    return (1);
}
