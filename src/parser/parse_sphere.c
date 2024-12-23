/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:45:11 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 16:34:59 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	sphere;
	char		**split;
	char		**color;
	char		**pos;

	split = ft_split(line, ' ');
	if (!validate_params(split, 4, "sphere"))
		return ;
	pos = ft_split(split[1], ',');
	if (!validate_coordinates(pos, "sphere", split))
		return ;
	set_sphere_center(&sphere, pos);
	sphere.radius = ft_atof(split[2]) / 2.0;
	color = ft_split(split[3], ',');
	if (!validate_coordinates(color, "sphere color", split))
	{
		ft_free_split(pos);
		return ;
	}
	sphere.material.color = create_material_color(color);
	init_sphere_material(&sphere);
	sphere.material.color = create_material_color(color);
	add_sphere(scene, &sphere);
	free_splits(split, pos, color);
}
