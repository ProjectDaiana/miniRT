/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_materials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:52:17 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/24 18:25:43 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_sphere_material(t_sphere *sphere)
{
	sphere->material.ambient = 0.2;
	sphere->material.diffuse = 0.7;
	sphere->material.specular = 0.7;
	sphere->material.shininess = 300;
	sphere->material.reflective = 0.0;
}

void	init_cylinder_material(t_cylinder *cylinder)
{
	cylinder->min = 0;
	cylinder->max = cylinder->height;
	cylinder->material.ambient = 0.2;
	cylinder->material.diffuse = 0.9;
	cylinder->material.specular = 0.1;
	cylinder->material.shininess = 100;
	cylinder->material.reflective = 0.0;
}

void	init_plane_material(t_plane *plane, t_color color)
{
	if (!plane)
		return ;
	plane->material.color = color;
	plane->material.ambient = 0.2;
	plane->material.diffuse = 0.9;
	plane->material.specular = 0.1;
	plane->material.shininess = 200;
	plane->material.reflective = 0.0;
	plane->material.transparency = 0.0;
	//plane->material.pattern.type = SOLID;
	plane->material.pattern.type = CHECKERS;
	plane->material.pattern.transform.m = NULL;
	if (plane->material.pattern.type == CHECKERS)
		set_plane_pattern(plane);
}
