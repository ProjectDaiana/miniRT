/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:44:49 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 20:36:59 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_ambient_component(t_color base_color, t_light_data *light_data)
{
	t_color	light_color;
	t_color	temp;
	double	ambient;

	light_color = light_data->light.color;
	ambient = light_data->material.ambient;
	temp = color_multiply_colors(base_color, light_color);
	return (color_multiply(temp, ambient * 1.8));
}

t_color	get_diffuse_component(t_color base_color, t_light_data *light_data,
		double dot)
{
	t_color	temp;
	double	factor;

	temp = color_multiply_colors(base_color, light_data->light.color);
	factor = light_data->material.diffuse * pow(dot, 1.1);
	factor *= light_data->light.intensity;
	return (color_multiply(temp, factor));
}

t_color	get_specular_component(t_light_data *light_data, double reflect_dot)
{
	double	factor;

	if (reflect_dot <= 0)
		return (create_color(0, 0, 0));
	factor = pow(reflect_dot, light_data->material.shininess);
	factor *= light_data->material.specular * light_data->light.intensity;
	return (color_multiply(light_data->light.color, factor));
}
