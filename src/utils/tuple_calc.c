/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:23:51 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 20:18:49 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	tuple_add(t_tuple a, t_tuple b)
{
	if (!is_valid_tuple(a) || !is_valid_tuple(b))
		return (create_vector(0, 0, 0));
	return (create_tuple(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
}

t_tuple	tuple_subtract(t_tuple a, t_tuple b)
{
	if (!is_valid_tuple(a) || !is_valid_tuple(b))
		return (create_vector(0, 0, 0));
	return (create_tuple(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w));
}

t_tuple	tuple_negate(t_tuple a)
{
	return (create_tuple(-a.x, -a.y, -a.z, -a.w));
}

t_tuple	tuple_multiply(t_tuple a, double scalar)
{
	t_tuple	result;

	if (!is_valid_tuple(a) || isnan(scalar) || isinf(scalar))
		return (create_vector(0, 0, 0));
	result = create_tuple(a.x * scalar, a.y * scalar, a.z * scalar, a.w
			* scalar);
	if (!is_valid_tuple(result))
		return (create_vector(0, 0, 0));
	return (result);
}

t_tuple	tuple_divide(t_tuple a, double scalar)
{
	return (create_tuple(a.x / scalar, a.y / scalar, a.z / scalar, a.w
			/ scalar));
}

t_tuple	tuple_reflect(t_tuple in, t_tuple normal)
{
	t_tuple	result;
	double	dot;

	if (!is_valid_tuple(in) || !is_valid_tuple(normal))
		return (create_vector(0, 0, 0));
	if (fabs(tuple_magnitude(normal) - 1.0) > EPSILON)
		normal = tuple_normalize(normal);
	if (!is_valid_tuple(normal))
		return (create_vector(0, 0, 0));
	dot = tuple_dot(in, normal);
	result = tuple_subtract(in, tuple_multiply(normal, 2.0 * dot));
	return (result);
}
