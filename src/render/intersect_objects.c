/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:35:59 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/27 17:40:34 by darotche         ###   ########.fr       */
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
	result.t = NULL;
	result.object = NULL;
	denom = tuple_dot(plane->normal, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		p0l0 = tuple_subtract(plane->point, ray.origin);
		t = tuple_dot(p0l0, plane->normal) / denom;
		if (t >= 0)
		{
			result.count = 1;
			result.t = ft_calloc(1, sizeof(double));
			result.object = ft_calloc(1, sizeof(void *));
			if (!result.t || !result.object)
			{
				free_intersections(&result);
				return (result);
			}
			result.t[0] = t;
			result.object[0] = plane;
		}
	}
	return (result);
}

// t_intersections	intersect_cylinder(t_cylinder cylinder, t_ray ray)
// {
// 	t_intersections	result;
// 	t_tuple			oc;
// 	double			a;
// 	double			b;
// 	double			c;

//     a = 0.0;
//     b = 0.0;
//     c = 0.0;
// 	result.count = 0;
// 	result.t = NULL;
// 	result.object = NULL;
// 	oc = tuple_subtract(ray.origin, cylinder.center);
// 	a = tuple_dot(ray.direction, ray.direction) - pow(tuple_dot(ray.direction,
// 				cylinder.axis), 2);
// 	b = 2 * (tuple_dot(ray.direction, oc) - tuple_dot(ray.direction,
// 				cylinder.axis) * tuple_dot(oc, cylinder.axis));
// 	c = tuple_dot(oc, oc) - pow(tuple_dot(oc, cylinder.axis), 2)
// 		- pow(cylinder.diameter / 2, 2);
// 	intersect_body(a, b, c, &result, cylinder, ray);
// 	intersect_caps(cylinder, ray, &result);
// 	return (result);
// }

t_intersections	intersect_cylinder(t_cylinder cylinder, t_ray ray)
{
	t_intersections	result;

	result.count = 0;
	result.capacity = 4;
	result.t = ft_calloc(result.capacity, sizeof(double));
	result.object = ft_calloc(result.capacity, sizeof(void *));
	if (!result.t || !result.object)
	{
		free_intersections(&result);
		result.capacity = 0;
		return (result);	
	}
	intersect_body(&cylinder, ray, &result);
	intersect_caps(&cylinder, ray, &result);
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
	if (scene->sphere_count > 0)
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
