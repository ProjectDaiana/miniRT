/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:09:03 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 21:15:03 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_cylinder(t_scene *scene, t_cylinder *cylinder)
{
	scene->cylinder_count++;
	scene->cylinders = realloc(scene->cylinders, scene->cylinder_count
			* sizeof(t_cylinder));
	scene->cylinders[scene->cylinder_count - 1] = *cylinder;
}

