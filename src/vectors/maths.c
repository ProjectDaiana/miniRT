/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:25:07 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 21:16:09 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_sqr(double x)
{
	return (x * x);
}

t_vector	vect_addition(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector	vect_multiplication(t_vector a, double b)
{
	t_vector	result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return (result);
}

void	calculate_t(double *t1, double *t2, double discriminant, double a,
		double b)
{
	double	temp;

	if (fabs(a) < EPSILON)
	{
		*t1 = *t2 = INFINITY;
		return ;
	}
	*t1 = (-b - sqrt(discriminant)) / (2 * a);
	*t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (*t1 > *t2)
	{
		temp = *t1;
		*t1 = *t2;
		*t2 = temp;
	}
}
