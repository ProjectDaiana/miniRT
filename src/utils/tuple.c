/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:24:05 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/26 19:02:59 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_valid_tuple(t_tuple t)
{
	t_tuple	zero;

	zero.x = 0.0;
	zero.y = 0.0;
	zero.z = 0.0;
	zero.w = 0.0;
	if (t.x != t.x || t.y != t.y || t.z != t.z || t.w != t.w || isinf(t.x)
		|| isinf(t.y) || isinf(t.z) || isinf(t.w))
		return (0);
	if (memcmp(&t, &zero, sizeof(t_tuple)) == 0)
		return (0);
	return (1);
}

double	tuple_magnitude(t_tuple a)
{
	double	mag;

	if (!is_valid_tuple(a))
		return (0.0);
	mag = sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
	if (mag != mag || isinf(mag))
		return (0.0);
	return (mag);
}

t_tuple	tuple_normalize(t_tuple a)
{
	double	mag;
	t_tuple	result;

	result = create_vector(0, 0, 0);
	mag = tuple_magnitude(a);
	if (fabs(mag) < EPSILON)
		return (result);
	result = tuple_divide(a, mag);
	if (fabs(tuple_magnitude(result) - 1.0) > EPSILON)
		return (create_vector(0, 0, 0));
	return (result);
}

double	tuple_dot(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

t_tuple	tuple_cross(t_tuple a, t_tuple b)
{
	if (fabs(a.w) > EPSILON || fabs(b.w) > EPSILON)
		return (create_vector(0, 0, 0));
	return (create_vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x
			* b.y - a.y * b.x));
}
