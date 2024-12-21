/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:19:45 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 20:19:48 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	transform_ray(t_ray ray, t_matrix transform)
{
	t_ray	result;

	result.origin = matrix_multiply_tuple(transform, ray.origin);
	result.direction = matrix_multiply_tuple(transform, ray.direction);
	return (result);
}
