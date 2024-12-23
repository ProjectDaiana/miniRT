/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:08:47 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 16:54:01 by darotche         ###   ########.fr       */
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

static t_color	get_intersection_color(t_scene *scene, t_ray ray, void *object,
		t_tuple point)
{
	t_tuple		normal;
	t_material	material;
	t_color		surface_color;
	t_compu		comps;

	normal = get_object_normal(object, point);
	material = get_object_material(object);
	comps.point = point;
	comps.eyev = tuple_negate(ray.direction);
	comps.normalv = normal;
	surface_color = get_surface_color(scene, material, comps);
	if (material.reflective > 0)
		return (blend_colors(surface_color, calculate_reflection(scene, ray,
					point, normal), material.reflective));
	return (surface_color);
}

static t_color	process_intersection(t_scene *scene, t_ray ray,
		t_intersections xs)
{
	t_tuple	point;
	void	*object;

	point = position(ray, xs.t[0]);
	object = xs.object[0];
	free_intersections(&xs);
	return (get_intersection_color(scene, ray, object, point));
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
