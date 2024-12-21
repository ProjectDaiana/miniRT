/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:56:11 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 20:56:20 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_camera_orientation(t_scene *scene, char **orient)
{
	scene->camera.orientation = create_vector(ft_atof(orient[0]),
			ft_atof(orient[1]), ft_atof(orient[2]));
}

void	set_camera_position(t_scene *scene, char **pos)
{
	scene->camera.position = create_point(ft_atof(pos[0]), ft_atof(pos[1]),
			ft_atof(pos[2]));
}
