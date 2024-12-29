/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:35:59 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 13:37:18 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_plane_intersections(t_scene *scene, t_ray ray,
		t_intersections *result)
{
	t_intersections	plane_xs;
	int				i;
	int				j;

	i = 0;
	while (i < scene->plane_count)
	{
		plane_xs = intersect_plane(&scene->planes[i], ray);
		j = 0;
		while (j < plane_xs.count)
		{
			result->t[result->count] = plane_xs.t[j];
			result->object[result->count] = &scene->planes[i];
			result->count++;
			j++;
		}
		free_intersections(&plane_xs);
		i++;
	}
}

void	add_cylinder_intersections(t_scene *scene, t_ray ray,
		t_intersections *result)
{
	t_intersections	cylinder_xs;
	int				i;
	int				j;

	i = 0;
	while (i < scene->cylinder_count)
	{
		cylinder_xs = intersect_cylinder(scene->cylinders[i], ray);
		j = 0;
		while (j < cylinder_xs.count)
		{
			result->t[result->count] = cylinder_xs.t[j];
			result->object[result->count] = &scene->cylinders[i];
			result->count++;
			j++;
		}
		free_intersections(&cylinder_xs);
		i++;
	}
	if (scene->cylinder_count > 0)
		free_intersections(&cylinder_xs);
}

void	add_sphere_intersections(t_scene *scene, t_ray ray,
		t_intersections *result)
{
	t_intersections	sphere_xs;
	int				i;
	int				j;

	i = 0;
	while (i < scene->sphere_count)
	{
		sphere_xs = intersect_sphere(scene->spheres[i], ray);
		j = 0;
		while (j < sphere_xs.count)
		{
			result->t[result->count] = sphere_xs.t[j];
			result->object[result->count] = &scene->spheres[i];
			result->count++;
			j++;
		}
		free_intersections(&sphere_xs);
		i++;
	}
}
