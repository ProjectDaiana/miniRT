/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:12:23 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 12:29:05 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersections	intersect_world(t_scene *scene, t_ray ray)
{
	t_intersections	result;
	int				max_intersections;

	init_world_intersection(&result);
	if (!scene || !is_valid_tuple(ray.origin) || !is_valid_tuple(ray.direction))
		return (result);
	max_intersections = scene->sphere_count * 2 + scene->plane_count
		+ scene->cylinder_count * 2;
	if (max_intersections <= 0)
		return (result);
	result.t = ft_calloc(max_intersections, sizeof(double));
	result.object = ft_calloc(max_intersections, sizeof(void *));
	if (!result.t || !result.object)
	{
		free_intersections(&result);
		return (result);
	}
	result.capacity = max_intersections;
	add_sphere_intersections(scene, ray, &result);
	add_plane_intersections(scene, ray, &result);
	add_cylinder_intersections(scene, ray, &result);
	if (result.count > 0)
		sort_intersections(&result);
	return (result);
}

void	add_intersection(t_intersections *result, double t, void *object)
{
	if (t > EPSILON)
	{
		if (result->count >= result->capacity)
			reallocate_intersection_arrays(result);
		if (result->t && result->object)
		{
			result->t[result->count] = t;
			result->object[result->count] = object;
			result->count++;
		}
	}
}

void	set_intersection_values(t_intersections *result, t_sphere *sphere,
		double *params)
{
	double	sqrt_disc;
	double	two_a;
	double	temp;

	sqrt_disc = sqrt(params[1] * params[1] - 4.0 * params[0] * params[2]);
	two_a = 2.0 * params[0];
	result->t[0] = (-params[1] - sqrt_disc) / two_a;
	result->t[1] = (-params[1] + sqrt_disc) / two_a;
	if (result->t[0] > result->t[1])
	{
		temp = result->t[0];
		result->t[0] = result->t[1];
		result->t[1] = temp;
	}
	result->object[0] = sphere;
	result->object[1] = sphere;
}

t_intersections	intersect_sphere(t_sphere sphere, t_ray ray)
{
	t_intersections	result;
	double			params[3];
	double			discriminant;

	params[0] = 0;
	params[1] = 0;
	params[2] = 0;
	ft_memset(&result, 0, sizeof(t_intersections));
	if (!is_valid_tuple(ray.origin) || !is_valid_tuple(ray.direction)
		|| !is_valid_tuple(sphere.center))
		return (result);
	calculate_sphere_params(ray, sphere, params);
	discriminant = (params[1] * params[1]) - (4.0 * params[0] * params[2]);
	if (discriminant >= 0 && params[0] != 0)
		init_intersection_result(&result);
	if (result.count > 0)
		set_intersection_values(&result, &sphere, params);
	return (result);
}
