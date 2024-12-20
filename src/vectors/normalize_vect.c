/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:25:13 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 20:25:14 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vect_length(double x, double y, double z)
{
	return (sqrt(ft_sqr(x) + ft_sqr(y) + ft_sqr(z)));
}

t_tuple	normalize_vect(t_tuple v)
{
	t_tuple	result;
	double	mag;

	mag = vect_length(v.x, v.y, v.z);
	if (mag == 0)
		return (v);
	result.x = v.x / mag;
	result.y = v.y / mag;
	result.z = v.z / mag;
	return (result);
}
