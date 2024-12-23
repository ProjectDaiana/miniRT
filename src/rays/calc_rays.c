/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:06:36 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 20:27:09 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	position(t_ray ray, double t)
{
	return (tuple_add(ray.origin, tuple_multiply(ray.direction, t)));
}

t_color	calculate_reflection_color(t_scene *scene, t_intersections xs,
		t_ray reflect_ray)
{
	t_tuple	reflect_point;
	void	*reflect_object;

	reflect_point = position(reflect_ray, xs.t[0]);
	reflect_object = xs.object[0];
	return (get_reflection_color(scene, reflect_ray, reflect_object,
			reflect_point));
}

t_color	calculate_reflection(t_scene *scene, t_ray ray, t_tuple point,
		t_tuple normal)
{
	t_ray			reflect_ray;
	t_intersections	reflect_xs;
	t_color			reflect_color;
	t_tuple			offset_point;

	offset_point = tuple_add(point, tuple_multiply(normal, 0.00001));
	reflect_ray = create_ray(offset_point, tuple_reflect(ray.direction,
				normal));
	reflect_color = create_color(0, 0, 0);
	reflect_xs = intersect_world(scene, reflect_ray);
	if (reflect_xs.count > 0)
	{
		reflect_color = calculate_reflection_color(scene, reflect_xs,
				reflect_ray);
		free_intersections(&reflect_xs);
		return (reflect_color);
	}
	free_intersections(&reflect_xs);
	return (reflect_color);
}
