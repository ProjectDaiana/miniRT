/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:45:12 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/22 16:46:51 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_ray	create_shadow_ray(t_tuple point, t_light *light)
{
	t_tuple	direction;
	t_tuple	normalized_direction;

	direction = tuple_subtract(light->position, point);
	normalized_direction = tuple_normalize(direction);
	return (create_ray(tuple_add(point, tuple_multiply(normalized_direction,
					EPSILON)), normalized_direction));
}

int	is_shadowed(t_scene *scene, t_tuple point, t_light *light)
{
	t_ray			shadow_ray;
	t_intersections	intersections;
	double			distance;
	int				i;

	shadow_ray = create_shadow_ray(point, light);
	distance = tuple_magnitude(tuple_subtract(light->position, point));
	intersections = intersect_world(scene, shadow_ray);
	i = 0;
	while (i < intersections.count)
	{
		if (intersections.t[i] > 0 && intersections.t[i] < distance)
			return (1);
		i++;
	}
	free_intersections(&intersections);
	return (0);
}

t_color	shade_hit(t_scene *scene, t_compu comps, int remaining)
{
	t_material			material;
	t_color				surface;
	t_color				reflected;
	int					shadowed;
	t_lighting_params	params;

	material = get_object_material(comps.object);
	shadowed = is_shadowed(scene, comps.over_point, &scene->light);
	params.material = material;
	params.light = scene->light;
	params.point = comps.point;
	params.eye_v = comps.eyev;
	params.normal_v = comps.normalv;
	params.in_shadow = shadowed;
	surface = lighting(params);
	reflected = reflected_color(scene, comps, remaining);
	return (color_add(surface, reflected));
}
