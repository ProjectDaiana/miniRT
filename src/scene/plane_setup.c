/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:59:06 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/24 18:26:34 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	init_plane_splits(char *line, char ***split, char ***pos,char ***normal)
// {
// 	*split = ft_split(line, ' ');
// 	if (!validate_params(*split, 4, "plane"))
// 		return (0);
// 	*pos = ft_split((*split)[1], ',');
// 	*normal = ft_split((*split)[2], ',');
// 	if (!validate_coordinates(*pos, "plane", *split)
// 		|| !validate_coordinates(*normal, "plane normal", *split))
// 	{
// 		free_splits(*split, *pos, *normal);
// 		return (0);
// 	}
// 	return (1);
// }

int	init_plane_splits(char *line, char ***split, char ***pos, char ***normal)
{
	*split = ft_split(line, ' ');
	if (!*split || !validate_params(*split, 4, "plane"))
	{
		if (*split)
			ft_free_split(*split);
		*split = NULL;
		return (0);
	}
	*pos = ft_split((*split)[1], ',');
	if (!*pos)
	{
		ft_free_split(*split);
		*split = NULL;
		return (0);
	}
	*normal = ft_split((*split)[2], ',');
	if (!*normal)
	{
		ft_free_split(*split);
		ft_free_split(*pos);
		*split = NULL;
		*pos = NULL;
		return (0);
	}
	if (!validate_coordinates(*pos, "plane", *split)
		|| !validate_coordinates(*normal, "plane normal", *split))
	{
		ft_free_split(*split);
		ft_free_split(*pos);
		ft_free_split(*normal);
		*split = NULL;
		*pos = NULL;
		*normal = NULL;
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

// t_plane	create_plane_from_params(char **pos, char **normal, char **color)
// {
// 	t_plane	plane;
// 	t_tuple	point;
// 	t_tuple	norm;
// 	t_color	col;
// 	int		color_count;

// 	ft_memset(&plane, 0, sizeof(t_plane));
// 	point = create_point(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]));
// 	norm = create_vector(ft_atof(normal[0]), ft_atof(normal[1]),
// 			ft_atof(normal[2]));
// 	// Initialize color first
// 	col = create_color(ft_atof(color[0]) / 255.0, ft_atof(color[1]) / 255.0,
// 			ft_atof(color[2]) / 255.0);
// 	printf("DEBUG: Parsed color values from .rt file: (%d, %d, %d)\n", col.r,
// 		col.g, col.b);
// 	// Create plane with the correct color
// 	plane = create_plane(point, norm, col);
// 	// Handle additional parameters
// 	color_count = 0;
// 	while (color[color_count])
// 		color_count++;
// 	if (color_count > 3)
// 		plane.material.reflective = ft_atof(color[3]);
// 	if (color_count > 4)
// 		plane.material.transparency = ft_atof(color[4]);
// 	return (plane);
// }

// void	add_plane(t_scene *scene, t_plane *plane)
// {
// 	scene->plane_count++;
// 	scene->planes = realloc(scene->planes, scene->plane_count
// 			* sizeof(t_plane));
// 	scene->planes[scene->plane_count - 1] = *plane;
// }

void	add_plane(t_scene *scene, t_plane *plane)
{
	t_plane	*new_planes;
	int		old_count;

	old_count = scene->plane_count;
	scene->plane_count++;
	new_planes = ft_calloc(scene->plane_count, sizeof(t_plane));
	if (!new_planes)
		return ;
	if (scene->planes)
	{
		for (int i = 0; i < old_count; i++)
		{
			new_planes[i] = scene->planes[i];
		}
		free(scene->planes);
	}
	new_planes[old_count] = *plane;
	scene->planes = new_planes;
}
