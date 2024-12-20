/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:44:59 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 19:47:22 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_light_data	init_light_data(t_lighting_params params)
{
	t_light_data	data;

	data.material = params.material;
	data.light = params.light;
	data.point = params.point;
	data.eye_v = params.eye_v;
	data.normal_v = params.normal_v;
	data.in_shadow = params.in_shadow;
	return (data);
}

static t_color	get_diffuse_and_specular(t_lighting_params params,
		t_tuple lightv, t_color base_color)
{
	t_light_data	data;
	t_color			diffuse;
	t_color			specular;
	t_tuple			reflectv;
	double			dot;

	data = init_light_data(params);
	dot = fmax(tuple_dot(lightv, params.normal_v), 0.0);
	diffuse = get_diffuse_component(base_color, &data, dot);
	reflectv = tuple_reflect(tuple_negate(lightv), params.normal_v);
	dot = fmax(tuple_dot(reflectv, params.eye_v), 0.0);
	specular = get_specular_component(&data, dot);
	return (color_add(diffuse, specular));
}

t_color	lighting(t_lighting_params params)
{
	t_light_data	data;
	t_color			base_color;
	t_color			ambient;
	t_tuple			lightv;
	t_color			final;

	data = init_light_data(params);
	base_color = get_base_color(params.material, params.point);
	ambient = get_ambient_component(base_color, &data);
	if (params.in_shadow)
		return (ambient);
	lightv = tuple_normalize(tuple_subtract(params.light.position,
				params.point));
	final = color_add(ambient, get_diffuse_and_specular(params, lightv,
				base_color));
	return (final);
}
