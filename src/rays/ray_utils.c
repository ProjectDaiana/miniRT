/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:08:38 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 15:47:41 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static int	is_cylinder(void *object)
// {
// 	t_cylinder	*cylinder;

// 	cylinder = (t_cylinder *)object;
// 	return (cylinder->diameter > 0 && cylinder->height > 0
// 		&& cylinder->axis.w == 0 && cylinder->center.w == 1.0
// 		&& fabs(tuple_magnitude(cylinder->axis) - 1.0) < EPSILON);
// }

int	is_cylinder(void *object)
{
	t_cylinder	*cylinder;
	double		mag;

	if (!object)
		return (0);
	cylinder = (t_cylinder *)object;
	if (!cylinder->axis.w && !cylinder->center.w)
		return (0);
	mag = tuple_magnitude(cylinder->axis);
	if (isnan(mag) || isinf(mag))
		return (0);
	return (cylinder->diameter > 0 && cylinder->height > 0
		&& cylinder->axis.w == 0 && cylinder->center.w == 1.0 && fabs(mag
			- 1.0) < EPSILON);
}


int	is_sphere(void *object)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)object;
	return (sphere->radius > 0 && sphere->center.w == 1.0
		&& sphere->material.color.r >= 0 && sphere->material.color.g >= 0
		&& sphere->material.color.b >= 0);
}

int	is_plane(void *object)
{
	t_plane	*plane;

	plane = (t_plane *)object;
	if (!plane || plane->point.w != 1.0 || plane->normal.w != 0.0)
		return (0);
	if (!(plane->normal.x != 0 || plane->normal.y != 0 || plane->normal.z != 0))
		return (0);
	return (1);
}

// t_material	get_object_material(void *object)
// {
// 	if (!object)
// 		return ((t_material){0});
// 	if (is_sphere(object))
// 		return (((t_sphere *)object)->material);
// 	if (is_cylinder(object))
// 		return (((t_cylinder *)object)->material);
// 	if (is_plane(object))
// 		return (((t_plane *)object)->material);
// 	return ((t_material){0});
// }

t_material	get_object_material(void *object)
{
	t_material	material;

	ft_memset(&material, 0, sizeof(t_material));
	if (!object)
		return (material);
	if (is_sphere(object))
		return (((t_sphere *)object)->material);
	if (is_cylinder(object))
		return (((t_cylinder *)object)->material);
	if (is_plane(object))
		return (((t_plane *)object)->material);
	return (material);
}

t_tuple	get_object_normal(void *object, t_tuple point)
{
	return (normal_at(object, point));
}

// t_color	get_reflection_color(t_scene *scene, t_ray reflect_ray,
// 		void *reflect_object, t_tuple reflect_point)
// {
// 	t_material			reflect_material;
// 	t_tuple				reflect_normal;
// 	t_tuple				reflect_eye;
// 	int					in_shadow;
// 	t_lighting_params	params;

// 	reflect_material = get_object_material(reflect_object);
// 	reflect_normal = get_object_normal(reflect_object, reflect_point);
// 	reflect_eye = tuple_negate(reflect_ray.direction);
// 	in_shadow = is_shadowed(scene, reflect_point, &scene->light);
// 	params = (t_lighting_params){reflect_material, scene->light, reflect_point,
// 		reflect_eye, reflect_normal, in_shadow};
// 	return (lighting(params));
// }

t_color	get_reflection_color(t_scene *scene, t_ray reflect_ray,
		void *reflect_object, t_tuple reflect_point)
{
	t_material			reflect_material;
	t_tuple				reflect_normal;
	t_tuple				reflect_eye;
	int					in_shadow;
	t_lighting_params	params;

	reflect_material = get_object_material(reflect_object);
	reflect_normal = get_object_normal(reflect_object, reflect_point);
	reflect_eye = tuple_negate(reflect_ray.direction);
	in_shadow = is_shadowed(scene, reflect_point, &scene->light);
	params = (t_lighting_params){reflect_material, scene->light, reflect_point,
		reflect_eye, reflect_normal, in_shadow};
	return (lighting(params));
}

t_color	get_surface_color(t_scene *scene, t_material material, t_compu comps)
{
	int					in_shadow;
	t_lighting_params	params;

	in_shadow = is_shadowed(scene, comps.point, &scene->light);
	params = (t_lighting_params){material, scene->light, comps.point,
		comps.eyev, comps.normalv, in_shadow};
	return (lighting(params));
}

t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}
