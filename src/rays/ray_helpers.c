/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:16:14 by tasha             #+#    #+#             */
/*   Updated: 2024/12/30 12:28:19 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	blend_colors(t_color surface_color, t_color reflect_color,
		double reflective)
{
	t_color	scaled_surface;
	t_color	scaled_reflection;

	scaled_surface = color_multiply(surface_color, 1.0 - reflective);
	scaled_reflection = color_multiply(reflect_color, reflective);
	return (color_add(scaled_surface, scaled_reflection));
}

void	init_cylinder_comps(t_compu *comps, t_cylinder *cylinder,
		t_tuple point)
{
	double	y;
	t_tuple	p;

	y = tuple_dot(tuple_subtract(point, cylinder->center), cylinder->axis);
	if (fabs(y - cylinder->height / 2) < EPSILON)
	{
		comps->normalv = cylinder->axis;
		comps->is_cap = 1;
	}
	else if (fabs(y + cylinder->height / 2) < EPSILON)
	{
		comps->normalv = tuple_negate(cylinder->axis);
		comps->is_cap = 1;
	}
	else
	{
		p = tuple_subtract(point, tuple_add(cylinder->center,
					tuple_multiply(cylinder->axis, y)));
		comps->normalv = tuple_normalize(p);
		comps->is_cap = 0;
	}
	comps->object = cylinder;
}

void	init_comps(t_compu *comps, void *object, t_tuple point, t_ray ray)
{
	comps->point = point;
	comps->eyev = tuple_negate(ray.direction);
	if (is_cylinder(object))
		init_cylinder_comps(comps, (t_cylinder *)object, point);
	else
		comps->normalv = get_object_normal(object, point);
	comps->over_point = tuple_add(point, tuple_multiply(comps->normalv,
				EPSILON));
	comps->object = object;
}

t_material	get_object_specific_material(void *object)
{
	if (is_cylinder(object))
		return (((t_cylinder *)object)->material);
	return (get_object_material(object));
}
