/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:51:05 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/21 22:56:48 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	calculate_minor(t_matrix *matrix, int row, int col, int mtrx_size)
{
	double		minor;
	t_matrix	submatrix;

	submatrix = find_submatrix(matrix, row, col, mtrx_size);
	minor = calculate_determinant(&submatrix, mtrx_size - 1);
	free_mtrx(&submatrix);
	return (minor);
}

double	calculate_cofactor(t_matrix *matrix, int row, int col, int mtrx_size)
{
	double	minor;
	double	cofactor;

	minor = calculate_minor(matrix, row, col, mtrx_size);
	if ((row + col) % 2 == 0)
		cofactor = minor;
	else
		cofactor = minor * -1;
	return (cofactor);
}

double	calculate_determinant(t_matrix *matrix, int size)
{
	int		i;
	double	det;

	det = 0.0;
	i = 0;
	if (size == 2)
	{
		det = matrix->m[0][0] * matrix->m[1][1] - matrix->m[0][1]
			* matrix->m[1][0];
		return (det);
	}
	else
	{
		while (i < size)
		{
			det += matrix->m[0][i] * calculate_cofactor(matrix, 0, i, size);
			i++;
		}
		return (det);
	}
}

double	calculate_determinant_m2(double **m, int size)
{
	double	determinant;

	if (size == 2)
	{
		determinant = m[0][0] * m[1][1] - m[0][1] * m[1][0];
		return (determinant);
	}
	return (0);
}
