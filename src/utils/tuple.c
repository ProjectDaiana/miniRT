/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:24:05 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 20:24:07 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	tuple_magnitude(t_tuple a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w));
}

t_tuple	tuple_normalize(t_tuple a)
{
	double	mag;

	mag = tuple_magnitude(a);
	return (tuple_divide(a, mag));
}

double	tuple_dot(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

t_tuple	tuple_cross(t_tuple a, t_tuple b)
{
	return (create_vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x
			* b.y - a.y * b.x));
}

t_tuple	tuple_reflect(t_tuple in, t_tuple normal)
{
	double	dot;

	dot = tuple_dot(in, normal);
	return (tuple_subtract(in, tuple_multiply(normal, 2 * dot)));
}
