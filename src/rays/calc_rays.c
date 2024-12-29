/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:06:36 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 00:08:39 by tasha            ###   ########.fr       */
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
	t_color default_color;

	default_color = create_color(0, 0, 0);
	
	if (!scene || !xs.t || !xs.object || xs.count <= 0)
		return (default_color);
		
	if (!is_valid_tuple(reflect_ray.origin) || !is_valid_tuple(reflect_ray.direction))
		return (default_color);
		
	reflect_point = position(reflect_ray, xs.t[0]);
	if (!is_valid_tuple(reflect_point))
		return (default_color);
		
	reflect_object = xs.object[0];
	if (!reflect_object)
		return (default_color);
		
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
	t_tuple			reflect_dir;

	reflect_color = create_color(0, 0, 0);
	
	if (!scene || !is_valid_tuple(point) || !is_valid_tuple(normal))
		return (reflect_color);
		
	reflect_dir = tuple_reflect(ray.direction, normal);
	printf("Reflection direction: (%f, %f, %f)\n", reflect_dir.x, reflect_dir.y, reflect_dir.z);
	
	if (!is_valid_tuple(reflect_dir))
		return (reflect_color);
		
	offset_point = tuple_add(point, tuple_multiply(normal, EPSILON));
	reflect_ray = create_ray(offset_point, reflect_dir);
	
	reflect_xs = intersect_world(scene, reflect_ray);
	if (reflect_xs.count > 0)
	{
		reflect_color = calculate_reflection_color(scene, reflect_xs,
				reflect_ray);
		printf("Reflection color: (%d, %d, %d)\n", reflect_color.r, reflect_color.g, reflect_color.b);
	}
	free_intersections(&reflect_xs);
	return (reflect_color);
}
