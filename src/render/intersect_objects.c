/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:35:59 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/21 21:35:31 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_intersections	intersect_plane(t_plane *plane, t_ray ray)
{
	double			denom;
	t_tuple			p0l0;
	double			t;
	t_intersections	result;

	result.count = 0;
	result.t1 = 0;
	result.t2 = 0;
	denom = tuple_dot(plane->normal, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		p0l0 = tuple_subtract(plane->point, ray.origin);
		t = tuple_dot(p0l0, plane->normal) / denom;
		if (t >= 0)
		{
			result.count = 1;
			result.t = malloc(sizeof(double));
			result.t[0] = t;
			result.object = malloc(sizeof(void *));
			result.object[0] = plane;
		}
	}
	return (result);
}

t_intersections	intersect_cylinder(t_cylinder cylinder, t_ray ray)
{
	t_intersections	result;
	t_tuple			oc;
	double			a;
	double			b;
	double			c;

	result.count = 0;
	result.t = NULL;
	result.object = NULL;
	oc = tuple_subtract(ray.origin, cylinder.center);
	a = tuple_dot(ray.direction, ray.direction) - pow(tuple_dot(ray.direction,
				cylinder.axis), 2);
	b = 2 * (tuple_dot(ray.direction, oc) - tuple_dot(ray.direction,
				cylinder.axis) * tuple_dot(oc, cylinder.axis));
	c = tuple_dot(oc, oc) - pow(tuple_dot(oc, cylinder.axis), 2)
		- pow(cylinder.diameter / 2, 2);
	intersect_body(a, b, c, &result, cylinder, ray);
	intersect_caps(cylinder, ray, &result);
	return (result);
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
		i++;
	}
	free_intersections(&sphere_xs);
}

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
		if (cylinder_xs.count > 0)
		{
			free(cylinder_xs.t);
			free(cylinder_xs.object);
		}
		i++;
	}
}
