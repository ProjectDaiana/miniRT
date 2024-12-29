/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:43:48 by tasha             #+#    #+#             */
/*   Updated: 2024/12/29 23:47:33 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	get_sphere_material(void *object)
{
	t_material	material;
	t_sphere	*sphere;

	ft_memset(&material, 0, sizeof(t_material));
	if (!is_sphere(object))
		return (material);
	sphere = (t_sphere *)object;
	if (!sphere)
		return (material);
	return (sphere->material);
}

t_material	get_plane_material(void *object)
{
	t_material	material;
	t_plane		*plane;

	ft_memset(&material, 0, sizeof(t_material));
	if (!is_plane(object))
		return (material);
	plane = (t_plane *)object;
	if (!plane)
		return (material);
	return (plane->material);
}

t_material	get_cylinder_material(void *object)
{
	t_material	material;
	t_cylinder	*cylinder;

	ft_memset(&material, 0, sizeof(t_material));
	if (!is_cylinder(object))
		return (material);
	cylinder = (t_cylinder *)object;
	if (!cylinder)
		return (material);
	return (cylinder->material);
}

t_material	get_object_material(void *object)
{
	t_material	material;

	ft_memset(&material, 0, sizeof(t_material));
	if (!object)
		return (material);
	if (is_sphere(object))
		return (get_sphere_material(object));
	if (is_cylinder(object))
		return (get_cylinder_material(object));
	if (is_plane(object))
		return (get_plane_material(object));
	return (material);
}

t_tuple	get_object_normal(void *object, t_tuple point)
{
	return (normal_at(object, point));
}
