/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:59:06 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/22 21:44:02 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_plane_splits(char *line, char ***split, char ***pos, char ***normal)
{
	*split = ft_split(line, ' ');
	if (!validate_params(*split, 4, "plane"))
		return (0);
	*pos = ft_split((*split)[1], ',');
	*normal = ft_split((*split)[2], ',');
	if (!validate_coordinates(*pos, "plane", *split)
		|| !validate_coordinates(*normal, "plane normal", *split))
	{
		free_splits(*split, *pos, *normal);
		return (0);
	}
	return (1);
}

t_plane	create_plane_from_params(char **pos, char **normal, char **color)
{
	t_plane	plane;
	t_tuple	point;
	t_tuple	norm;
	int		color_count;

	point = create_point(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]));
	norm = create_vector(ft_atof(normal[0]), ft_atof(normal[1]),
			ft_atof(normal[2]));
	plane = create_plane(point, norm, create_material_color(color));
	color_count = 0;
	while (color[color_count])
		color_count++;
	if (color_count > 3)
		plane.material.reflective = ft_atof(color[3]);
	if (color_count > 4)
		plane.material.transparency = ft_atof(color[4]);
	return (plane);
}

void	add_plane(t_scene *scene, t_plane *plane)
{
	t_plane	*new_planes;

	scene->plane_count++;
	new_planes = ft_calloc(scene->plane_count, sizeof(t_plane));
	if (scene->planes)
	{
		ft_memcpy(new_planes, scene->planes, (scene->plane_count - 1) * sizeof(t_plane));
		free(scene->planes);
	}
	scene->planes = new_planes;
	scene->planes[scene->plane_count - 1] = *plane;
}
