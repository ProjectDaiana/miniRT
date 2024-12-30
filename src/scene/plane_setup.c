/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:59:06 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 12:29:55 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_plane_splits(char *line, char ***split, char ***pos, char ***normal)
{
	if (!validate_and_split_line(line, split))
		return (0);
	if (!validate_and_split_pos(split, pos))
		return (0);
	if (!validate_and_split_normal(split, pos, normal))
		return (0);
	return (1);
}

t_plane	create_plane_from_params(char **pos, char **normal, char **color)
{
	t_plane	plane;
	t_tuple	point;
	t_tuple	norm;
	int		color_count;

	ft_memset(&plane, 0, sizeof(t_plane));
	point = create_point(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]));
	norm = create_vector(ft_atof(normal[0]), ft_atof(normal[1]),
			ft_atof(normal[2]));
	plane.material.color.r = ft_atof(color[0]) / 255.0;
	plane.material.color.g = ft_atof(color[1]) / 255.0;
	plane.material.color.b = ft_atof(color[2]) / 255.0;
	plane = create_plane(point, norm, plane.material.color);
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
	int		old_count;

	old_count = scene->plane_count;
	scene->plane_count++;
	new_planes = ft_calloc(scene->plane_count, sizeof(t_plane));
	if (!new_planes)
		return ;
	copy_existing_planes(new_planes, scene, old_count);
	new_planes[old_count] = *plane;
	scene->planes = new_planes;
}
