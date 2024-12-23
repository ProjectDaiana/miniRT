/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:49:27 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 20:06:01 by tasha            ###   ########.fr       */
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
}

// void	free_scene(t_scene *scene)
// {
// 	if (scene->cylinders)
// 	{
// 		free(scene->cylinders);
// 		scene->cylinders = NULL;
// 	}
// 	if (scene->planes)
// 	{
// 		free(scene->planes);
// 		scene->planes = NULL;
// 	}
// 	if (scene->spheres)
// 	{
// 		free(scene->spheres);
// 		scene->spheres = NULL;
// 	}
// 	if (scene->lights)
// 	{
// 		free(scene->lights);
// 		scene->lights = NULL;
// 	}
// }


void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;

	if (scene->spheres)
	{
		free(scene->spheres);
		scene->spheres = NULL;
	}

	if (scene->planes)
	{
		for (int i = 0; i < scene->plane_count; i++)
		{
			if (scene->planes[i].transform.m)
				free_mtrx(&scene->planes[i].transform);
		}
		free(scene->planes);
		scene->planes = NULL;
	}

	if (scene->cylinders)
	{
		for (int i = 0; i < scene->cylinder_count; i++)
		{
			if (scene->cylinders[i].transform.m)
				free_mtrx(&scene->cylinders[i].transform);
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