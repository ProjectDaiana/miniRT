/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:49:27 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/26 20:12:11 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_intersections(t_intersections *xs)
{
	if (!xs)
		return ;
	if (xs->t)
	{
		free(xs->t);
		xs->t = NULL;
	}
	if (xs->object)
	{
		free(xs->object);
		xs->object = NULL;
	}
	xs->count = 0;
	xs->capacity = 0;
}

void	free_scene(t_scene *scene)
{
	int	i;

	if (!scene)
		return ;
	if (scene->camera.transform.m)
	{
		free_mtrx(&scene->camera.transform);
		scene->camera.transform.m = NULL;
	}
	if (scene->spheres)
	{
		for (i = 0; i < scene->sphere_count; i++)
		{
			if (scene->spheres[i].material.pattern.transform.m)
			{
				free_pattern(&scene->spheres[i].material.pattern);
				scene->spheres[i].material.pattern.transform.m = NULL;
			}
		}
		free(scene->spheres);
		scene->spheres = NULL;
	}
	if (scene->planes)
	{
		for (i = 0; i < scene->plane_count; i++)
		{
			if (scene->planes[i].material.pattern.transform.m)
			{
				free_pattern(&scene->planes[i].material.pattern);
				scene->planes[i].material.pattern.transform.m = NULL;
			}
			if (scene->planes[i].transform.m)
			{
				free_mtrx(&scene->planes[i].transform);
				scene->planes[i].transform.m = NULL;
			}
		}
		free(scene->planes);
		scene->planes = NULL;
	}
	if (scene->cylinders)
	{
		for (i = 0; i < scene->cylinder_count; i++)
		{
			if (scene->cylinders[i].material.pattern.transform.m)
			{
				free_pattern(&scene->cylinders[i].material.pattern);
				scene->cylinders[i].material.pattern.transform.m = NULL;
			}
			if (scene->cylinders[i].transform.m)
			{
				free_mtrx(&scene->cylinders[i].transform);
				scene->cylinders[i].transform.m = NULL;
			}
		}
		free(scene->cylinders);
		scene->cylinders = NULL;
	}
	if (scene->lights)
	{
		free(scene->lights);
		scene->lights = NULL;
	}
	scene->sphere_count = 0;
	scene->plane_count = 0;
	scene->cylinder_count = 0;
	scene->light_count = 0;
}
