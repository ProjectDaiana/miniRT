/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:09:03 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/22 21:44:23 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_cylinder(t_scene *scene, t_cylinder *cylinder)
{
	t_cylinder	*new_cylinders;

	scene->cylinder_count++;
	new_cylinders = ft_calloc(scene->cylinder_count, sizeof(t_cylinder));
	if (!new_cylinders)
		return ;
	if (scene->cylinders)
	{
		ft_memcpy(new_cylinders, scene->cylinders, (scene->cylinder_count - 1)
				* sizeof(t_cylinder));
		free(scene->cylinders);
	}
	scene->cylinders = new_cylinders;
	scene->cylinders[scene->cylinder_count - 1] = *cylinder;
}
