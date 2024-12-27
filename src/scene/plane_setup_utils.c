/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_setup_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:06:02 by tasha             #+#    #+#             */
/*   Updated: 2024/12/26 20:08:37 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_and_split_line(char *line, char ***split)
{
	*split = ft_split(line, ' ');
	if (!*split || !validate_params(*split, 4, "plane"))
	{
		if (*split)
			ft_free_split(*split);
		*split = NULL;
		return (0);
	}
	return (1);
}

int	validate_and_split_pos(char ***split, char ***pos)
{
	*pos = ft_split((*split)[1], ',');
	if (!*pos)
	{
		ft_free_split(*split);
		*split = NULL;
		return (0);
	}
	return (1);
}

int	validate_and_split_normal(char ***split, char ***pos, char ***normal)
{
	*normal = ft_split((*split)[2], ',');
	if (!*normal || !validate_coordinates(*pos, "plane", *split)
		|| !validate_coordinates(*normal, "plane normal", *split))
	{
		ft_free_split(*split);
		ft_free_split(*pos);
		if (*normal)
			ft_free_split(*normal);
		*split = NULL;
		*pos = NULL;
		*normal = NULL;
		return (0);
	}
	return (1);
}

void	copy_existing_planes(t_plane *new_planes, t_scene *scene, int old_count)
{
	if (scene->planes)
	{
		ft_memcpy(new_planes, scene->planes, old_count * sizeof(t_plane));
		free(scene->planes);
	}
}
