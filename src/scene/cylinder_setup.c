/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:09:03 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 23:53:15 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_cylinder(t_scene *scene, t_cylinder *cylinder)
{
	t_cylinder	*new_cylinders;
	int			old_count;

	old_count = scene->cylinder_count;
	scene->cylinder_count++;
	new_cylinders = ft_calloc(scene->cylinder_count, sizeof(t_cylinder));
	if (!new_cylinders)
		return ;
	if (scene->cylinders)
	{
		for (int i = 0; i < old_count; i++)
		{
			new_cylinders[i] = scene->cylinders[i];
		}
		free(scene->cylinders);
	}
	new_cylinders[old_count] = *cylinder;
	scene->cylinders = new_cylinders;
}
