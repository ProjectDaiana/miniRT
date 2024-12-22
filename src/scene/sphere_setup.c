/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:57:18 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/22 22:30:21 by darotche         ###   ########.fr       */
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
	t_sphere	*new_spheres;

	scene->sphere_count++;
	new_spheres = ft_calloc(scene->sphere_count, sizeof(t_sphere));
	if (scene->spheres)
	{
		ft_memcpy(new_spheres, scene->spheres, (scene->sphere_count - 1)
				* sizeof(t_sphere));
		free(scene->spheres);
	}
	scene->spheres = new_spheres;
	scene->spheres[scene->sphere_count - 1] = *sphere;
}
