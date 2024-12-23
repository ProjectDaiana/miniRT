/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:24:05 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 15:49:10 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int is_valid_tuple(t_tuple t)
{
	return (!isnan(t.x) && !isnan(t.y) && !isnan(t.z) && !isnan(t.w)
		&& !isinf(t.x) && !isinf(t.y) && !isinf(t.z) && !isinf(t.w));
}

double	tuple_magnitude(t_tuple a)
{
	// Check for NaN/Inf values in components
	if (isnan(a.x) || isnan(a.y) || isnan(a.z) || isnan(a.w) ||
		isinf(a.x) || isinf(a.y) || isinf(a.z) || isinf(a.w))
		return 0.0;
	
	// Calculate magnitude
	double mag = sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
	
	// Check for NaN/Inf result
	if (isnan(mag) || isinf(mag))
		return 0.0;
	
	return mag;
}

t_tuple	tuple_normalize(t_tuple a)
{
	double	mag;
	t_tuple	result;

	// Initialize result to zero vector
	result = create_vector(0, 0, 0);
	
	mag = tuple_magnitude(a);
	if (fabs(mag) < EPSILON)
		return result; 
	
	// Safely divide
	result = tuple_divide(a, mag);
	
	// Validate result
	if (fabs(tuple_magnitude(result) - 1.0) > EPSILON)
		return create_vector(0, 0, 0);
	
	return result;
}

double	tuple_dot(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

t_tuple	tuple_cross(t_tuple a, t_tuple b)
{
	if (fabs(a.w) > EPSILON || fabs(b.w) > EPSILON) // here
		return (create_vector(0, 0, 0)); // here
	return (create_vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x
			* b.y - a.y * b.x));
}

t_tuple	tuple_reflect(t_tuple in, t_tuple normal)
{
	double	dot;
	double	normal_mag;

	normal_mag = tuple_magnitude(normal); // here
	if (fabs(normal_mag - 1.0) > EPSILON) // here
		normal = tuple_divide(normal, normal_mag); // here
	dot = tuple_dot(in, normal);
	return (tuple_subtract(in, tuple_multiply(normal, 2 * dot)));
}
