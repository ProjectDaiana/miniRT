/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:49:27 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 19:49:30 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_intersections(t_intersections *xs)
{
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

void	free_scene(t_scene *scene)
{
	if (scene->cylinders)
	{
		free(scene->cylinders);
		scene->cylinders = NULL;
	}
	if (scene->planes)
	{
		free(scene->planes);
		scene->planes = NULL;
	}
	if (scene->spheres)
	{
		free(scene->spheres);
		scene->spheres = NULL;
	}
	if (scene->lights)
	{
		free(scene->lights);
		scene->lights = NULL;
	}
}
