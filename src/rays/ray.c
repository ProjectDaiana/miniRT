/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:08:47 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 12:28:35 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
