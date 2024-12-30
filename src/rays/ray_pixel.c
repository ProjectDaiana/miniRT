/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:12:48 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 12:28:23 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_tuple	get_pixel_position(t_camera *cam, int px, int py)
{
	double	xoffset;
	double	yoffset;
	double	world_x;
	double	world_y;

	xoffset = (px + 0.5) * cam->pixel_size;
	yoffset = (py + 0.5) * cam->pixel_size;
	world_x = cam->half_width - xoffset;
	world_y = cam->half_height - yoffset;
	return (create_point(world_x, world_y, -1));
}

// t_ray	ray_for_pixel(t_camera *cam, int px, int py)
// {
// 	t_matrix	inv_transform;
// 	t_tuple		pixel;
// 	t_tuple		origin;
// 	t_tuple		direction;

// 	inv_transform = inverse_matrix(&cam->transform);
// 	pixel = transform_point(inv_transform, get_pixel_position(cam, px, py));
// 	origin = transform_point(inv_transform, create_point(0, 0, 0));
// 	direction = tuple_normalize(tuple_subtract(pixel, origin));
// 	free_mtrx(&inv_transform);
// 	return (create_ray(origin, direction));
// }

t_ray	ray_for_pixel(t_camera *cam, int px, int py)
{
	t_matrix	inv_transform;
	t_tuple		pixel;
	t_tuple		origin;
	t_tuple		direction;
	t_ray		result;

	result = create_ray(create_point(0, 0, 0), create_vector(0, 0, 1));
	if (!cam || !cam->transform.m)
		return (result);
	inv_transform = inverse_matrix(&cam->transform);
	if (!inv_transform.m)
		return (result);
	pixel = transform_point(inv_transform, get_pixel_position(cam, px, py));
	origin = transform_point(inv_transform, create_point(0, 0, 0));
	if (!is_valid_tuple(pixel) || !is_valid_tuple(origin)
		|| tuple_magnitude(tuple_subtract(pixel, origin)) < EPSILON)
	{
		free_mtrx(&inv_transform);
		return (result);
	}
	direction = tuple_normalize(tuple_subtract(pixel, origin));
	free_mtrx(&inv_transform);
	return (create_ray(origin, direction));
}
