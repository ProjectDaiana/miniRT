/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:45:05 by tasha             #+#    #+#             */
/*   Updated: 2024/12/30 12:29:34 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_cylinder(void *object)
{
	t_cylinder	*cylinder;
	double		mag;

	if (!object)
		return (0);
	cylinder = (t_cylinder *)object;
	if (!is_valid_tuple(cylinder->axis) || !is_valid_tuple(cylinder->center))
		return (0);
	if (cylinder->axis.w != 0 || cylinder->center.w != 1.0)
		return (0);
	if (cylinder->diameter <= 0 || cylinder->height <= 0)
		return (0);
	mag = tuple_magnitude(cylinder->axis);
	if (isnan(mag) || isinf(mag) || fabs(mag - 1.0) >= EPSILON)
		return (0);
	return (1);
}

int	is_sphere(void *object)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)object;
	return (sphere->radius > 0 && sphere->center.w == 1.0
		&& sphere->material.color.r >= 0 && sphere->material.color.g >= 0
		&& sphere->material.color.b >= 0);
}

int	is_plane(void *object)
{
	t_plane	*plane;

	plane = (t_plane *)object;
	if (!plane || plane->point.w != 1.0 || plane->normal.w != 0.0)
		return (0);
	if (!(plane->normal.x != 0 || plane->normal.y != 0 || plane->normal.z != 0))
		return (0);
	return (1);
}
