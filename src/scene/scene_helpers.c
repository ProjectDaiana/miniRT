/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:17:22 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/26 19:22:33 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_light(t_scene *scene, t_light *light)
{
	t_light	*new_lights;

	scene->light_count++;
	new_lights = ft_calloc(scene->light_count, sizeof(t_light));
	if (scene->lights)
	{
		ft_memcpy(new_lights, scene->lights, (scene->light_count - 1)
			* sizeof(t_light));
		free(scene->lights);
	}
	scene->lights = new_lights;
	scene->lights[scene->light_count - 1] = *light;
}
