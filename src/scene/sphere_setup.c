/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:57:18 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 21:10:06 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_sphere_center(t_sphere *sphere, char **pos)
{
	sphere->center = create_point(ft_atof(pos[0]), ft_atof(pos[1]),
			ft_atof(pos[2]));
}

void	add_sphere(t_scene *scene, t_sphere *sphere)
{
	scene->sphere_count++;
	scene->spheres = realloc(scene->spheres, scene->sphere_count
			* sizeof(t_sphere));
	scene->spheres[scene->sphere_count - 1] = *sphere;
}

