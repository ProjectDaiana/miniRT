#include "minirt.h"



// t_matrix create_matrix(double m[4][4])
// {
// 	t_matrix matrix;

// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			matrix.m[i][j] = m[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (matrix);
//}

// t_matrix create_matrix_3(double m[3][3])
// {
// 	t_matrix matrix;

// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < 3)
// 	{
// 		j = 0;
// 		while (j < 3)
// 		{
// 			matrix.m[i][j] = m[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (matrix);
// }

t_matrix	create_matrix(int size)
{
	int i;
	t_matrix	matrix;

	i = 0;
	matrix.size = size;
	matrix.m = ft_calloc(size, sizeof(double *));
	while (i < size)
	{
		matrix.m[i] = malloc(sizeof(double) * size);
		i++;
	}
	return (matrix);
}

void	assign_matrix_3(t_matrix *matrix, double m[3][3])
{
	int i;
	int j;

	i = 0;
	while (i < matrix->size)
	{
		j = 0;
		while (j < matrix->size)
		{
			matrix->m[i][j] = m[i][j];
			j++;
		}
		i++;
	}
}

void	assign_matrix(t_matrix *matrix, double m[4][4])
{
	int i;
	int j;

	i = 0;
	while (i < matrix->size)
	{
		j = 0;
		while (j < matrix->size)
		{
			matrix->m[i][j] = m[i][j];
			j++;
		}
		i++;
	}
}

int	compare_matrix(t_matrix a, t_matrix b)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (a.m[i][j] != b.m[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

// Multiply matrix by matrix. This is similar to the dot product of two vectors
t_matrix matrix_multiply(t_matrix a, t_matrix b)
{
	t_matrix result;
	result = create_matrix(4);
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];
			j++;
		}
		i++;
	}
	return (result);
}

t_tuple multiply_matrix_by_tuple(t_matrix *matrix, t_tuple *tuple)
{
    t_tuple result;

    result.x = matrix->m[0][0] * tuple->x + matrix->m[0][1] * tuple->y + matrix->m[0][2] * tuple->z + matrix->m[0][3] * tuple->w;
    result.y = matrix->m[1][0] * tuple->x + matrix->m[1][1] * tuple->y + matrix->m[1][2] * tuple->z + matrix->m[1][3] * tuple->w;
    result.z = matrix->m[2][0] * tuple->x + matrix->m[2][1] * tuple->y + matrix->m[2][2] * tuple->z + matrix->m[2][3] * tuple->w;
    result.w = matrix->m[3][0] * tuple->x + matrix->m[3][1] * tuple->y + matrix->m[3][2] * tuple->z + matrix->m[3][3] * tuple->w;

    return result;
}

t_matrix	transpose_matrix(t_matrix *identity_matrix)
{
	t_matrix transposed;
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			transposed.m[i][j] = identity_matrix->m[j][i];
			j++;
		}
		i++;
	}
	return (transposed);
}

t_matrix	find_submatrix(t_matrix *matrix, int row, int col, int mtrx_size)
{
	t_matrix submatrix;
	submatrix = create_matrix(mtrx_size - 1);
	int i;
	int j;
	int sub_i;
	int sub_j;

	i = 0;
	sub_i = 0;
	while (i < mtrx_size)
	{
		if (i == row)
		{
			i++;
			continue;
		}
		j = 0;
		sub_j = 0;
		while (j < mtrx_size)
		{
			if (j == col)
			{
				j++;
				continue;
			}
			submatrix.m[sub_i][sub_j] = matrix->m[i][j];
			j++;
			sub_j++;
		}
		i++;
		sub_i++;
	}
	return (submatrix);
}

// Minor is the Determinant of the submatrix at(i,j)
double	calculate_minor(t_matrix *matrix, int row, int col, int mtrx_size)
{
	double minor;
	t_matrix submatrix;
	
	submatrix = find_submatrix(matrix, row, col, mtrx_size);
	print_matrix(submatrix, "Submatrix in calculate_minor()", mtrx_size -1);
	minor = calculate_determinant(&submatrix, mtrx_size - 1);
 	printf(MAG"Minor: %f\n"RESET, minor);
 	return (minor);
 }

// Cofactor is the minor with the sign changed
 double calculate_cofactor(t_matrix *matrix, int row, int col, int mtrx_size)
 {
	double	minor;
	double	cofactor;

	minor = calculate_minor(matrix, row, col, mtrx_size);
	if ((row + col) % 2 == 0)
		cofactor = minor;
	else
		cofactor = minor * -1;
	printf(MAG"Cofactor: %f\n"RESET, cofactor);
	return (cofactor);
 }

// Supports 2x2,  3x3 and 4x4 matrices
 double calculate_determinant(t_matrix *matrix, int size)
 {
	int		i;
	double	det;

	det = 0.0;
	i = 0;
	if (size == 2)
	{
		det = matrix->m[0][0] * matrix->m[1][1] - matrix->m[0][1] * matrix->m[1][0];
		printf(MAG"calculate_determinant(): %f\n"RESET, det);
		return (det);
	}
	else
	{
		while (i < size)
		{
			det += matrix->m[0][i] * calculate_cofactor(matrix, 0, i, size);
			i++;
		}
		printf(MAG"calculate_determinant(): %f\n"RESET, det);
		return (det);
	}
 }

// Determinant for 2x2 matrix
// double calculate_determinant_m2(double **m, int size)
// {
// 	double determinant;

// 	if (size == 2)
// 	{
// 		determinant = m[0][0] * m[1][1] - m[0][1] * m[1][0];
// 		//printf(MAG"calculate_determinant(): %f\n"RESET, determinant);
// 		return (determinant);
// 	}
// 	print_error("Matrix size not supported");
// 	return (0);
// }

// double calculate_determinant(double m[2][2])
// {
// 	double determinant;

// 	determinant = m[0][0] * m[1][1] - m[0][1] * m[1][0];
// 	printf(MAG"Determinant: %f\n"RESET, determinant);
// 	return (determinant);
// }
