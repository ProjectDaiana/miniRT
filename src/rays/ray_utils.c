/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:08:38 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 23:47:10 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_reflection_params(t_lighting_params *params,
		t_material material, t_scene *scene, t_reflection_data data)
{
	ft_memset(params, 0, sizeof(t_lighting_params));
	params->material = material;
	params->light = scene->light;
	params->point = data.point;
	params->eye_v = data.eye;
	params->normal_v = data.normal;
	params->in_shadow = data.in_shadow;
}

static t_reflection_data	get_cylinder_reflection(t_cylinder *cylinder,
		t_tuple reflect_point)
{
	t_reflection_data	data;
	double				y;
	t_tuple				p;

	y = tuple_dot(tuple_subtract(reflect_point, cylinder->center),
			cylinder->axis);
	data.material = cylinder->material;
	if (fabs(y - cylinder->height / 2) < EPSILON)
	{
		data.normal = cylinder->axis;
		data.material.reflective *= 0.5;
	}
	else if (fabs(y + cylinder->height / 2) < EPSILON)
	{
		data.normal = tuple_negate(cylinder->axis);
		data.material.reflective *= 0.5;
	}
	else
	{
		p = tuple_subtract(reflect_point, tuple_add(cylinder->center,
					tuple_multiply(cylinder->axis, y)));
		data.normal = tuple_normalize(p);
	}
	return (data);
}

t_color	get_reflection_color(t_scene *scene, t_ray reflect_ray,
		void *reflect_object, t_tuple reflect_point)
{
	t_reflection_data	data;
	t_lighting_params	params;
	t_color				default_color;

	default_color = create_color(0, 0, 0);
	if (!scene || !reflect_object || !is_valid_tuple(reflect_point))
		return (default_color);
	if (is_cylinder(reflect_object))
		data = get_cylinder_reflection((t_cylinder *)reflect_object,
				reflect_point);
	else
	{
		data.material = get_object_material(reflect_object);
		data.normal = get_object_normal(reflect_object, reflect_point);
	}
	if (!is_valid_tuple(data.normal))
		return (default_color);
	data.eye = tuple_negate(reflect_ray.direction);
	if (!is_valid_tuple(data.eye))
		return (default_color);
	data.in_shadow = is_shadowed(scene, reflect_point, &scene->light);
	data.point = reflect_point;
	init_reflection_params(&params, data.material, scene, data);
	return (lighting(params));
}

t_color	get_surface_color(t_scene *scene, t_material material, t_compu comps)
{
	int					in_shadow;
	t_lighting_params	params;

	ft_memset(&params, 0, sizeof(t_lighting_params));
	in_shadow = is_shadowed(scene, comps.point, &scene->light);
	params = (t_lighting_params){material, scene->light, comps.point,
		comps.eyev, comps.normalv, in_shadow};
	return (lighting(params));
}

t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}
