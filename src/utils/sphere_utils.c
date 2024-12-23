/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:18:20 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 16:40:07 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calculate_sphere_params(t_ray ray, t_sphere sphere, double *params)
{
	t_tuple	sphere_to_ray;

	if (!params || !is_valid_tuple(ray.origin) || !is_valid_tuple(ray.direction) || 
		!is_valid_tuple(sphere.center))
		return;

	sphere_to_ray = tuple_subtract(ray.origin, sphere.center);
	if (!is_valid_tuple(sphere_to_ray))
		return;

	params[0] = tuple_dot(ray.direction, ray.direction);
	params[1] = 2.0 * tuple_dot(ray.direction, sphere_to_ray);
	params[2] = tuple_dot(sphere_to_ray, sphere_to_ray) - (sphere.radius * sphere.radius);
}
