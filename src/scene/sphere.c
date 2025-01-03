/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:18:34 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 12:30:09 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	create_sphere(void)
{
	t_sphere	sphere;

	sphere.center = create_point(0, 0, 0);
	sphere.radius = 1.0;
	sphere.material.ambient = 0.2;
	sphere.material.diffuse = 0.7;
	sphere.material.specular = 0.7;
	sphere.material.shininess = 300;
	sphere.material.reflective = 0.1;
	return (sphere);
}

t_tuple	normal_at(void *object, t_tuple world_point)
{
	t_tuple	normal;

	if (!object || !is_valid_tuple(world_point))
		return (create_vector(0, 0, 0));
	normal = create_vector(0, 0, 0);
	if (is_sphere(object))
		return (normal_at_sphere((t_sphere *)object, world_point));
	if (is_cylinder(object))
		return (normal_at_cylinder((t_cylinder *)object, world_point));
	if (is_plane(object))
		return (normal_at_plane((t_plane *)object, world_point));
	return (normal);
}
