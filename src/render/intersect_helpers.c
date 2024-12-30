/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:11:34 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 12:28:47 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calculate_cylinder_intersections(t_cylinder cylinder, t_ray ray,
		double *t, double *y)
{
	double	params[3];

	calculate_cylinder_params(cylinder, ray, params);
	if (params[1] * params[1] - 4 * params[0] * params[2] >= 0)
	{
		t[0] = (-params[1] - sqrt(params[1] * params[1] - 4 * params[0]
					* params[2])) / (2 * params[0]);
		t[1] = (-params[1] + sqrt(params[1] * params[1] - 4 * params[0]
					* params[2])) / (2 * params[0]);
		y[0] = ray.origin.y + t[0] * ray.direction.y;
		y[1] = ray.origin.y + t[1] * ray.direction.y;
	}
	else
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
	}
}

void	check_cylinder_bounds(t_cylinder cylinder, double *t, double *y)
{
	if (!t || !y)
		return ;
	if (y[0] < -cylinder.height / 2 || y[0] > cylinder.height / 2)
		t[0] = INFINITY;
	if (y[1] < -cylinder.height / 2 || y[1] > cylinder.height / 2)
		t[1] = INFINITY;
}

void	init_intersection_result(t_intersections *result)
{
	result->count = 2;
	result->t = ft_calloc(2, sizeof(double));
	result->object = ft_calloc(2, sizeof(void *));
	if (!result->t || !result->object)
	{
		free_intersections(result);
		result->count = 0;
	}
}
