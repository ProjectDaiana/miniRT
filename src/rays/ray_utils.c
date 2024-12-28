/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:08:38 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/28 17:00:31 by darotche         ###   ########.fr       */
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
	if (!is_valid_tuple(cylinder->axis) || !is_valid_tuple(cylinder->center))
		return (0);
	if (cylinder->axis.w != 0 || cylinder->center.w != 1.0)
		return (0);
	if (cylinder->diameter <= 0 || cylinder->height <= 0)
		return (0);
	mag = tuple_magnitude(cylinder->axis);
	if (isnan(mag) || isinf(mag) || fabs(mag - 1.0) >= EPSILON)
		return (0);
	return (1);
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
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane		*plane;

	ft_memset(&material, 0, sizeof(t_material));
	if (!object)
		return (material);
	if (is_sphere(object))
	{
		sphere = (t_sphere *)object;
		if (!sphere)
			return (material);
		return (sphere->material);
	}
	if (is_cylinder(object))
	{
		cylinder = (t_cylinder *)object;
		if (!cylinder)
			return (material);
		return (cylinder->material);
	}
	if (is_plane(object))
	{
		plane = (t_plane *)object;
		if (!plane)
			return (material);
		return (plane->material);
	}
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
	t_color				default_color;

	default_color = create_color(0, 0, 0);
	if (!scene || !reflect_object || !is_valid_tuple(reflect_point))
		return (default_color);
	reflect_material = get_object_material(reflect_object);
	reflect_normal = get_object_normal(reflect_object, reflect_point);
	if (!is_valid_tuple(reflect_normal))
		return (default_color);
	reflect_eye = tuple_negate(reflect_ray.direction);
	if (!is_valid_tuple(reflect_eye))
		return (default_color);
	in_shadow = is_shadowed(scene, reflect_point, &scene->light);
	ft_memset(&params, 0, sizeof(t_lighting_params));
	params.material = reflect_material;
	params.light = scene->light;
	params.point = reflect_point;
	params.eye_v = reflect_eye;
	params.normal_v = reflect_normal;
	params.in_shadow = in_shadow;
	return (lighting(params));
}

t_color	get_surface_color(t_scene *scene, t_material material, t_compu comps)
{
	int					in_shadow;
	t_lighting_params	params;

	ft_memset(&params, 0, sizeof(t_lighting_params));
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
