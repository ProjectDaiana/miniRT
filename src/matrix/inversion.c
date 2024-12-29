/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inversion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:50:57 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 20:48:31 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_invertible(double det)
{
	if (isnan(det) || isinf(det))
		return (0);
	if (fabs(det) < EPSILON)
		return (0);
	return (1);
}

static void	fill_inverse_matrix(t_matrix *matrix, t_matrix *inverse,
		double determinant)
{
	int		i;
	int		j;
	double	cofactor;

	i = 0;
	while (i < matrix->size)
	{
		j = 0;
		while (j < matrix->size)
		{
			cofactor = calculate_cofactor(matrix, i, j, matrix->size);
			inverse->m[j][i] = cofactor / determinant;
			j++;
		}
		i++;
	}
}

t_matrix	inverse_matrix(t_matrix *matrix)
{
	t_matrix	inverse;
	double		determinant;

	if (!matrix || !matrix->m || matrix->size <= 0)
		return (create_identity_matrix());
	inverse = create_matrix(matrix->size);
	if (!inverse.m)
		return (create_identity_matrix());
	determinant = calculate_determinant(matrix, matrix->size);
	if (!is_invertible(determinant))
	{
		free_mtrx(&inverse);
		return (create_identity_matrix());
	}
	fill_inverse_matrix(matrix, &inverse, determinant);
	return (inverse);
}
