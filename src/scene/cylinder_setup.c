/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:09:03 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 12:29:28 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	copy_existing_cylinders(t_cylinder *new_cylinders, t_scene *scene,
		int old_count)
{
	if (scene->cylinders)
	{
		ft_memcpy(new_cylinders, scene->cylinders, old_count
			* sizeof(t_cylinder));
		free(scene->cylinders);
	}
}

void	add_cylinder(t_scene *scene, t_cylinder *cylinder)
{
	t_cylinder	*new_cylinders;
	int			old_count;

	old_count = scene->cylinder_count;
	scene->cylinder_count++;
	new_cylinders = ft_calloc(scene->cylinder_count, sizeof(t_cylinder));
	if (!new_cylinders)
		return ;
	copy_existing_cylinders(new_cylinders, scene, old_count);
	new_cylinders[old_count] = *cylinder;
	scene->cylinders = new_cylinders;
}
