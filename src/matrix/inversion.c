/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inversion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:50:57 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/23 16:11:05 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	is_invertible(double det)
// {
// 	if (fabs(det) < EPSILON)
// 	{
// 		return (0);
// 	}
// 	return (1);
// }

int	is_invertible(double det)
{
	if (isnan(det) || isinf(det))
		return (0);
	if (fabs(det) < EPSILON)
		return (0);
	return (1);
}

// static void	fill_inverse_matrix(t_matrix *matrix, t_matrix *inverse,
// 		double determinant)
// {
// 	int		i;
// 	int		j;
// 	double	cofactor;

// 	i = 0;
// 	while (i < matrix->size)
// 	{
// 		j = 0;
// 		while (j < matrix->size)
// 		{
// 			cofactor = calculate_cofactor(matrix, i, j, matrix->size);
// 			inverse->m[j][i] = cofactor / determinant;
// 			j++;
// 		}
// 		i++;
// 	}
// }

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

// t_matrix	inverse_matrix(t_matrix *matrix)
// {
// 	t_matrix	inverse;
// 	double		determinant;
// 	int			size;

// 	size = matrix->size;
// 	inverse = create_matrix(size);
// 	determinant = calculate_determinant(matrix, size);
// 	if (!is_invertible(determinant))
// 		return (create_identity_matrix());
// 	fill_inverse_matrix(matrix, &inverse, determinant);
// 	return (inverse);
// }

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
