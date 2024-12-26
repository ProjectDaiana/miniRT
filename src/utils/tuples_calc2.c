/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_calc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:05:53 by tasha             #+#    #+#             */
/*   Updated: 2024/12/26 19:06:30 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
