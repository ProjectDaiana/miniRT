/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:17:22 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 21:20:53 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_light(t_scene *scene, t_light *light)
{
	scene->light_count++;
	scene->lights = realloc(scene->lights, scene->light_count
			* sizeof(t_light));
	scene->lights[scene->light_count - 1] = *light;
}
