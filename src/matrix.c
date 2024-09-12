#include "minirt.h"

// Create matrix
t_matrix	create_matrix(double m[4][4])
{
	t_matrix	matrix;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			matrix.m[i][j] = m[i][j];
			j++;
		}
		i++;
	}
	return (matrix);
}

void	print_matrix(t_matrix matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%f ", matrix.m[i][j]);
		printf("\n");
	}
}

int	compare_matrix(t_matrix a, t_matrix b)
{
	int	i;
	int	j;

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
t_matrix	matrix_multiply(t_matrix a, t_matrix b)
{
	t_matrix	result;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j]
				+ a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];
			j++;
		}
		i++;
	}
	return (result);
}

t_tuple	multiply_matrix_by_tuple(t_matrix *matrix, t_tuple *tuple)
{
	t_tuple	result;

	result.x = matrix->m[0][0] * tuple->x + matrix->m[0][1] * tuple->y
		+ matrix->m[0][2] * tuple->z + matrix->m[0][3] * tuple->w;
	result.y = matrix->m[1][0] * tuple->x + matrix->m[1][1] * tuple->y
		+ matrix->m[1][2] * tuple->z + matrix->m[1][3] * tuple->w;
	result.z = matrix->m[2][0] * tuple->x + matrix->m[2][1] * tuple->y
		+ matrix->m[2][2] * tuple->z + matrix->m[2][3] * tuple->w;
	result.w = matrix->m[3][0] * tuple->x + matrix->m[3][1] * tuple->y
		+ matrix->m[3][2] * tuple->z + matrix->m[3][3] * tuple->w;
	return (result);
}

// added today?

t_matrix	create_identity_matrix(void)
{
	t_matrix	identity;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			identity.m[i][j] = (i == j) ? 1.0 : 0.0;
		}
	}
	return (identity);
}

t_matrix	create_translation_matrix(double x, double y, double z)
{
	t_matrix	translation;

	translation = create_identity_matrix();
	translation.m[0][3] = x;
	translation.m[1][3] = y;
	translation.m[2][3] = z;
	return (translation);
}

t_matrix	create_scaling_matrix(double x, double y, double z)
{
	t_matrix	scaling;

	scaling = create_identity_matrix();
	scaling.m[0][0] = x;
	scaling.m[1][1] = y;
	scaling.m[2][2] = z;
	return (scaling);
}

t_matrix	inverse_matrix(t_matrix m)
{
	t_matrix	inv;
	double		det;
	double		inv_det;

	det = m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1])
		- m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0])
		+ m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]);
	inv_det = 1.0 / det;
	inv.m[0][0] = (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]) * inv_det;
	inv.m[0][1] = (m.m[0][2] * m.m[2][1] - m.m[0][1] * m.m[2][2]) * inv_det;
	inv.m[0][2] = (m.m[0][1] * m.m[1][2] - m.m[0][2] * m.m[1][1]) * inv_det;
	inv.m[1][0] = (m.m[1][2] * m.m[2][0] - m.m[1][0] * m.m[2][2]) * inv_det;
	inv.m[1][1] = (m.m[0][0] * m.m[2][2] - m.m[0][2] * m.m[2][0]) * inv_det;
	inv.m[1][2] = (m.m[0][2] * m.m[1][0] - m.m[0][0] * m.m[1][2]) * inv_det;
	inv.m[2][0] = (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]) * inv_det;
	inv.m[2][1] = (m.m[0][1] * m.m[2][0] - m.m[0][0] * m.m[2][1]) * inv_det;
	inv.m[2][2] = (m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0]) * inv_det;
	return (inv);
}

t_matrix	create_rotation_x_matrix(double angle)
{
	t_matrix	rotation;

	rotation = create_identity_matrix();
	rotation.m[1][1] = cos(angle);
	rotation.m[1][2] = -sin(angle);
	rotation.m[2][1] = sin(angle);
	rotation.m[2][2] = cos(angle);
	return (rotation);
}

t_matrix	create_rotation_y_matrix(double angle)
{
	t_matrix	rotation;

	rotation = create_identity_matrix();
	rotation.m[0][0] = cos(angle);
	rotation.m[0][2] = sin(angle);
	rotation.m[2][0] = -sin(angle);
	rotation.m[2][2] = cos(angle);
	return (rotation);
}

t_matrix	create_rotation_z_matrix(double angle)
{
	t_matrix	rotation;

	rotation = create_identity_matrix();
	rotation.m[0][0] = cos(angle);
	rotation.m[0][1] = -sin(angle);
	rotation.m[1][0] = sin(angle);
	rotation.m[1][1] = cos(angle);
	return (rotation);
}

t_vector	apply_matrix_to_vector(t_matrix m, t_vector v)
{
	t_vector result;
	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3];
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3];
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3];
	return (result);
}