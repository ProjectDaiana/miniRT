/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:57:18 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/26 19:40:58 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_sphere_center(t_sphere *sphere, char **pos)
{
	sphere->center = create_point(ft_atof(pos[0]), ft_atof(pos[1]),
			ft_atof(pos[2]));
}

static void	copy_existing_spheres(t_sphere *new_spheres, t_scene *scene,
		int old_count)
{
	if (scene->spheres)
	{
		ft_memcpy(new_spheres, scene->spheres, old_count * sizeof(t_sphere));
		free(scene->spheres);
	}
}

void	add_sphere(t_scene *scene, t_sphere *sphere)
{
	t_sphere	*new_spheres;
	int			old_count;

	old_count = scene->sphere_count;
	scene->sphere_count++;
	new_spheres = ft_calloc(scene->sphere_count, sizeof(t_sphere));
	if (!new_spheres)
		return ;
	copy_existing_spheres(new_spheres, scene, old_count);
	new_spheres[old_count] = *sphere;
	scene->spheres = new_spheres;
}
