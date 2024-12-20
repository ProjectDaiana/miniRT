/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:12:23 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 21:36:46 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_intersections	intersect_world(t_scene *scene, t_ray ray)
{
	t_intersections	result;
	int				max_intersections;

	result.count = 0;
	result.t = NULL;
	result.object = NULL;
	max_intersections = scene->sphere_count * 2 + scene->plane_count
		+ scene->cylinder_count * 2;
	result.t = malloc(sizeof(double) * max_intersections);
	result.object = malloc(sizeof(void *) * max_intersections);
	add_sphere_intersections(scene, ray, &result);
	add_plane_intersections(scene, ray, &result);
	add_cylinder_intersections(scene, ray, &result);
	sort_intersections(&result);
	return (result);
}

void	add_intersection(t_intersections *result, double t)
{
	double	*new_t;

	if (result->count == 0)
	{
		result->t = ft_calloc(1, sizeof(double));
	}
	else
	{
		new_t = ft_calloc(result->count + 1, sizeof(double));
		if (!new_t)
		{
			fprintf(stderr,
				"Error: Memory allocation failed in add_intersection\n");
			exit(1);
		}
		ft_memcpy(new_t, result->t, sizeof(double) * result->count);
		free(result->t);
		result->t = new_t;
	}
	if (!result->t)
	{
		fprintf(stderr,
			"Error: Memory allocation failed in add_intersection\n");
		exit(1);
	}
	result->t[result->count] = t;
	result->count++;
}

void	init_intersection_result(t_intersections *result, double discriminant)
{
	result->count = 0;
	result->t = NULL;
	result->object = NULL;
	if (discriminant >= 0)
	{
		result->count = 2;
		result->t = malloc(sizeof(double) * 2);
		result->object = malloc(sizeof(void *) * 2);
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

	calculate_sphere_params(ray, sphere, params);
	discriminant = (params[1] * params[1]) - (4.0 * params[0] * params[2]);
	init_intersection_result(&result, discriminant);
	if (discriminant >= 0)
		set_intersection_values(&result, &sphere, params);
	return (result);
}


void	allocate_intersections(t_intersections *result, double *t,
		t_cylinder *cylinder)
{
	int	index;

	result->count = (t[0] != INFINITY) + (t[1] != INFINITY);
	if (result->count > 0)
	{
		result->t = malloc(sizeof(double) * result->count);
		result->object = malloc(sizeof(void *) * result->count);
		index = 0;
		if (t[0] != INFINITY)
			add_valid_intersection(result, t[0], cylinder, &index);
		if (t[1] != INFINITY)
			add_valid_intersection(result, t[1], cylinder, &index);
	}
}
