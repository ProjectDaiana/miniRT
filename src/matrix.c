#include "minirt.h"

//Create matrix
t_matrix	create_matrix(int size)
{
	int i;
	t_matrix	matrix;

	i = 0;
	matrix.size = size;
	matrix.m = malloc(sizeof(double *) * size);
	while (i < size)
	{
		matrix.m[i] = malloc(sizeof(double) * size);
		i++;
	}
	return (matrix);
}

void	free_matrix(t_matrix *matrix)
{
	int i;

	i = 0;
	while (i < matrix->size)
	{
		free(matrix->m[i]);
		i++;
	}
	free(matrix->m);
}

// void populate_matrix(t_matrix *matrix, double values[][4], int size) {
//     matrix->size = size;
//     matrix->m = (double **)malloc(size * sizeof(double *));
//     for (int i = 0; i < size; i++) {
//         matrix->m[i] = (double *)malloc(size * sizeof(double));
//         for (int j = 0; j < size; j++) {
//             matrix->m[i][j] = values[i][j];
//         }
//     }
// }

// void	create_and_populate_matrix(t_matrix *matrix, double *values, int size)
// {
// 	int i;
// 	int j;

// 	printf(MAG"Creating and populating matrix\n"RESET);
// 	matrix->size = size;
// 	matrix->m = (double **)malloc(size * sizeof(double *));
// 	if (matrix->m == NULL)
// 		print_error("Error: Memory allocation failed\n");
// 	i = 0;
// 	while (i < size)
// 	{
// 		printf("i: %d\n", i);
// 		j = 0;
// 		matrix->m[i] = (double *)malloc(size * sizeof(double));
// 		if (matrix->m[i] == NULL)
// 			print_error("Error: Memory allocation failed\n");
// 		while (j < size) {
// 			printf("j: %d\n", j);
// 			matrix->m[i][j] = values[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// }

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

t_matrix create_matrix_3(double m[3][3])
{
	t_matrix matrix;

	int i;
	int j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			matrix.m[i][j] = m[i][j];
			j++;
		}
		i++;
	}
	return (matrix);
}

void print_matrix(t_matrix matrix, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf(YEL"%s\n"RESET ,str);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%f ", matrix.m[i][j]);
			j++;
		}
		printf("\n");
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

double calculate_determinant(double m[2][2])
{
	double determinant;

	determinant = m[0][0] * m[1][1] - m[0][1] * m[1][0];
	printf(MAG"Determinant: %f\n"RESET, determinant);
	return (determinant);
}


// ATTENTION! It is returning a 4x4 matrix replacen the corresponding values with 0.000
t_matrix	find_submatrix(t_matrix *matrix, int row, int col, int mtrx_size)
{
	t_matrix submatrix;
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
	print_matrix(submatrix, "Submatrix");
	return (submatrix);
}


// Determinant of the submatrix
double	calculate_minor(t_matrix *matrix, int row, int col, int mtrx_size)
{
	t_matrix submatrix;
	double minor;
	double determinant;

	submatrix = find_submatrix(matrix, row, col, mtrx_size);
	determinant = calculate_determinant((double (*)[2])submatrix.m);
	minor = determinant;
	if ((row + col) % 2 != 0)
		minor *= -1;
	printf(MAG"Minor: %f\n"RESET, minor);
	return (minor);
}