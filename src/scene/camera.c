/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:14:50 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 21:14:51 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	create_camera(int hsize, int vsize, double field_of_view)
{
	t_camera	cam;
	double		half_view;
	double		aspect;

	cam.height = hsize;
	cam.width = vsize;
	cam.fov = field_of_view;
	cam.transform = create_identity_matrix();
	half_view = tan(field_of_view / 2);
	aspect = (double)hsize / vsize;
	if (aspect >= 1)
	{
		cam.half_width = half_view;
		cam.half_height = half_view / aspect;
	}
	else
	{
		cam.half_width = half_view * aspect;
		cam.half_height = half_view;
	}
	cam.pixel_size = (cam.half_width * 2) / hsize;
	return (cam);
}
