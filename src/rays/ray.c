/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:08:47 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/26 19:39:52 by darotche         ###   ########.fr       */
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

// static t_color	get_intersection_color(t_scene *scene, t_ray ray,
//		void *object,
// 		t_tuple point)
// {
// 	t_tuple		normal;
// 	t_material	material;
// 	t_color		surface_color;
// 	t_compu		comps;

// 	normal = get_object_normal(object, point);
// 	material = get_object_material(object);
// 	comps.point = point;
// 	comps.eyev = tuple_negate(ray.direction);
// 	comps.normalv = normal;
// 	surface_color = get_surface_color(scene, material, comps);
// 	if (material.reflective > 0)
// 		return (blend_colors(surface_color, calculate_reflection(scene, ray,
// 					point, normal), material.reflective));
// 	return (surface_color);
// }


static t_color	get_intersection_color(t_scene *scene, t_ray ray, void *object,
		t_tuple point)
{
	t_tuple		normal;
	t_material	material;
	t_color		surface_color;
	t_compu		comps;

	surface_color = create_color(0, 0, 0);
	if (!scene || !object || !is_valid_tuple(point))
		return (surface_color);
	
	ft_memset(&comps, 0, sizeof(t_compu));

	if (is_cylinder(object))
    {
        t_cylinder *cylinder = (t_cylinder *)object;
        double y = tuple_dot(tuple_subtract(point, cylinder->center), cylinder->axis);
        if (fabs(y - cylinder->height / 2) < EPSILON)
            normal = cylinder->axis;
        else if (fabs(y + cylinder->height / 2) < EPSILON)
            normal = tuple_negate(cylinder->axis);
        else
        {
            t_tuple p = tuple_subtract(point, tuple_add(cylinder->center, tuple_multiply(cylinder->axis, y)));
            normal = tuple_normalize(p);
        }
    }
    else
    {
        normal = get_object_normal(object, point);
    }
	//normal = get_object_normal(object, point);
	if (!is_valid_tuple(normal))
		return (surface_color);
	
	material = get_object_material(object);
	comps.point = point;
	comps.eyev = tuple_negate(ray.direction);
	comps.normalv = normal;
	comps.object = object;
	
	surface_color = get_surface_color(scene, material, comps);
	if (material.reflective > 0)
	{
		t_color reflect_color = calculate_reflection(scene, ray, point, normal);
		surface_color = blend_colors(surface_color, reflect_color, material.reflective);
	}
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
