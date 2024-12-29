/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:08:47 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 15:59:37 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	blend_colors(t_color surface_color, t_color reflect_color,
		double reflective)
{
	t_color	scaled_surface;
	t_color	scaled_reflection;

	scaled_surface = color_multiply(surface_color, 1.0 - reflective);
	scaled_reflection = color_multiply(reflect_color, reflective);
	return (color_add(scaled_surface, scaled_reflection));
}

static void	init_cylinder_comps(t_compu *comps, t_cylinder *cylinder,
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

static void	init_comps(t_compu *comps, void *object, t_tuple point, t_ray ray)
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

static t_material	get_object_specific_material(void *object)
{
	if (is_cylinder(object))
		return (((t_cylinder *)object)->material);
	return (get_object_material(object));
}

static t_color	get_intersection_color(t_scene *scene, t_ray ray, void *object,
		t_tuple point)
{
	t_compu		comps;
	t_material	material;
	t_color		surface_color;
	t_color		reflect_color;

	if (!scene || !object || !is_valid_tuple(point))
		return (create_color(0, 0, 0));
	ft_memset(&comps, 0, sizeof(t_compu));
	init_comps(&comps, object, point, ray);
	if (!is_valid_tuple(comps.normalv))
		return (create_color(0, 0, 0));
	material = get_object_specific_material(object);
	surface_color = get_surface_color(scene, material, comps);
	if (material.reflective > 0)
	{
		reflect_color = calculate_reflection(scene, ray, point, comps.normalv);
		surface_color = blend_colors(surface_color, reflect_color,
				material.reflective);
	}
	return (surface_color);
}

static t_color	process_intersection(t_scene *scene, t_ray ray,
		t_intersections xs)
{
	t_tuple	point;
	void	*object;
	t_color	color;

	point = position(ray, xs.t[0]);
	object = xs.object[0];
	color = get_intersection_color(scene, ray, object, point);
	free_intersections(&xs);
	return (color);
}

t_color	ray_color(t_scene *scene, t_ray ray)
{
	t_intersections	xs;

	xs = intersect_world(scene, ray);
	if (xs.count > 0)
		return (process_intersection(scene, ray, xs));
	free_intersections(&xs);
	return (create_color(0, 0, 0));
}
