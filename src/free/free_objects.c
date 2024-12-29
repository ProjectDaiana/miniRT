/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:25:43 by darotche          #+#    #+#             */
/*   Updated: 2024/12/29 23:34:26 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_camera_transform(t_camera *camera)
{
	if (camera->transform.m)
	{
		free_mtrx(&camera->transform);
		camera->transform.m = NULL;
	}
}

void	free_spheres(t_sphere *spheres, int sphere_count)
{
	int	i;

	i = 0;
	while (i < sphere_count)
	{
		if (spheres[i].material.pattern.transform.m)
		{
			free_pattern(&spheres[i].material.pattern);
			spheres[i].material.pattern.transform.m = NULL;
		}
		i++;
	}
	free(spheres);
}

void	free_planes(t_plane *planes, int plane_count)
{
	int	i;

	i = 0;
	while (i < plane_count)
	{
		if (planes[i].material.pattern.transform.m)
		{
			free_pattern(&planes[i].material.pattern);
			planes[i].material.pattern.transform.m = NULL;
		}
		if (planes[i].transform.m)
		{
			free_mtrx(&planes[i].transform);
			planes[i].transform.m = NULL;
		}
		i++;
	}
	free(planes);
}

void	free_cylinders(t_cylinder *cylinders, int cylinder_count)
{
	int	i;

	i = 0;
	while (i < cylinder_count)
	{
		if (cylinders[i].material.pattern.transform.m)
		{
			free_pattern(&cylinders[i].material.pattern);
			cylinders[i].material.pattern.transform.m = NULL;
		}
		if (cylinders[i].transform.m)
		{
			free_mtrx(&cylinders[i].transform);
			cylinders[i].transform.m = NULL;
		}
		i++;
	}
	free(cylinders);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_camera_transform(&scene->camera);
	if (scene->spheres)
		free_spheres(scene->spheres, scene->sphere_count);
	if (scene->planes)
		free_planes(scene->planes, scene->plane_count);
	if (scene->cylinders)
		free_cylinders(scene->cylinders, scene->cylinder_count);
	if (scene->lights)
		free(scene->lights);
	scene->sphere_count = 0;
	scene->plane_count = 0;
	scene->cylinder_count = 0;
	scene->light_count = 0;
}
