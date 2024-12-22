/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:18:20 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/22 23:24:46 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calculate_sphere_params(t_ray ray, t_sphere sphere, double *params)
{
	t_tuple	sphere_to_ray;

	if (!params) // here
		return ;
	sphere_to_ray = tuple_subtract(ray.origin, sphere.center);
	params[0] = tuple_dot(ray.direction, ray.direction);
	params[1] = 2.0 * tuple_dot(ray.direction, sphere_to_ray);
	params[2] = tuple_dot(sphere_to_ray, sphere_to_ray) - (sphere.radius
			* sphere.radius);
}
