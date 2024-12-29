/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:45:11 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 21:34:49 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sphere_details(char **split, t_sphere *sphere, t_scene *scene)
{
	char	**color;
	char	**pos;

	pos = ft_split(split[1], ',');
	if (!validate_coordinates(pos, "sphere", split))
	{
		free_splits(split, pos, NULL);
		return ;
	}
	set_sphere_center(sphere, pos);
	sphere->radius = ft_atof(split[2]) / 2.0;
	color = ft_split(split[3], ',');
	if (!validate_coordinates(color, "sphere color", split))
	{
		free_splits(split, pos, color);
		return ;
	}
	sphere->material.color = create_material_color(color);
	init_sphere_material(sphere);
	add_sphere(scene, sphere);
	free_splits(split, pos, color);
}

void	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	sphere;
	char		**split;

	ft_memset(&sphere, 0, sizeof(t_sphere));
	sphere.material.ambient = 0.1;
	sphere.material.diffuse = 0.9;
	sphere.material.specular = 0.9;
	sphere.material.shininess = 200.0;
	sphere.material.reflective = 0.0;
	sphere.material.transparency = 0.0;
	sphere.material.has_pattern = 0;
	split = ft_split(line, ' ');
	if (!validate_params(split, 4, "sphere"))
	{
		ft_free_split(split);
		return ;
	}
	parse_sphere_details(split, &sphere, scene);
}
