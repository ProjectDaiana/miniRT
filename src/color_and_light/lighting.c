/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:03:54 by darotche          #+#    #+#             */
/*   Updated: 2024/12/29 23:08:16 by darotche         ###   ########.fr       */
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

	ft_memset(&data, 0, sizeof(t_light_data));
	diffuse = create_color(0, 0, 0);
	specular = create_color(0, 0, 0);
	reflectv = create_vector(0, 0, 0);
	if (tuple_magnitude(lightv) < EPSILON
		|| tuple_magnitude(params.normal_v) < EPSILON
		|| tuple_magnitude(params.eye_v) < EPSILON)
		return (diffuse);
	data = init_light_data(params);
	dot = fmax(tuple_dot(lightv, params.normal_v), 0.0);
	diffuse = get_diffuse_component(base_color, &data, dot);
	reflectv = tuple_reflect(tuple_negate(lightv), params.normal_v);
	if (tuple_magnitude(reflectv) < EPSILON)
		return (diffuse);
	dot = fmax(tuple_dot(reflectv, params.eye_v), 0.0);
	specular = get_specular_component(&data, dot);
	return (color_add(diffuse, specular));
}

static t_color	calculate_lighting_components(t_lighting_params params,
		t_light_data data, t_color base_color)
{
	t_color	final;
	t_color	ambient;
	t_tuple	lightv;

	final = create_color(0, 0, 0);
	ambient = get_ambient_component(base_color, &data);
	if (params.in_shadow)
		return (ambient);
	lightv = tuple_normalize(tuple_subtract(params.light.position,
				params.point));
	if (tuple_magnitude(lightv) < EPSILON)
		return (ambient);
	final = color_add(ambient, get_diffuse_and_specular(params, lightv,
				base_color));
	return (final);
}

static int	validate_lighting_params(t_lighting_params params)
{
	double	point_mag;
	double	eye_mag;
	double	normal_mag;

	if (!is_valid_tuple(params.point) || !is_valid_tuple(params.eye_v)
		|| !is_valid_tuple(params.normal_v))
		return (0);
	point_mag = tuple_magnitude(params.point);
	eye_mag = tuple_magnitude(params.eye_v);
	normal_mag = tuple_magnitude(params.normal_v);
	if (isnan(point_mag) || isnan(eye_mag) || isnan(normal_mag)
		|| point_mag < EPSILON || eye_mag < EPSILON || normal_mag < EPSILON)
		return (0);
	return (1);
}

t_color	lighting(t_lighting_params params)
{
	t_light_data	data;
	t_color			final;
	t_color			base_color;

	final = create_color(0, 0, 0);
	ft_memset(&data, 0, sizeof(t_light_data));
	if (!validate_lighting_params(params))
		return (final);
	data = init_light_data(params);
	base_color = get_base_color(params.material, params.point);
	final = calculate_lighting_components(params, data, base_color);
	final = clamp_color(final);
	return (final);
}
