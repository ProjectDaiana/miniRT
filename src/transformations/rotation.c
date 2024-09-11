#include "minirt.h"

t_matrix	rotation_x(double rad)
{
	t_matrix rotation_matrix;

	rotation_matrix = create_matrix(4);
	rotation_matrix.m[0][0] = 1;
	rotation_matrix.m[1][1] = cos(rad);
	rotation_matrix.m[1][2] = -sin(rad);
	rotation_matrix.m[2][1] = sin(rad);
	rotation_matrix.m[2][2] = cos(rad);
	rotation_matrix.m[3][3] = 1;
	print_matrix(rotation_matrix, "Rotation Matrix", 4);
	return (rotation_matrix);
}

t_matrix	rotation_y(double rad)
{
	t_matrix rotation_matrix;

	rotation_matrix = create_matrix(4);
	rotation_matrix.m[0][0] = cos(rad);
	rotation_matrix.m[0][2] = sin(rad);
	rotation_matrix.m[2][0] = -sin(rad);
	rotation_matrix.m[2][2] = cos(rad);
	rotation_matrix.m[1][1] = 1;
	rotation_matrix.m[3][3] = 1;
	print_matrix(rotation_matrix, "Rotation Matrix", 4);
	return (rotation_matrix);
}

t_matrix	rotation_z(double rad)
{
	t_matrix rotation_matrix;

	rotation_matrix = create_matrix(4);
	rotation_matrix.m[0][0] = cos(rad);
	rotation_matrix.m[0][1] = -sin(rad);
	rotation_matrix.m[1][0] = sin(rad);
	rotation_matrix.m[1][1] = cos(rad);
	rotation_matrix.m[2][2] = 1;
	rotation_matrix.m[3][3] = 1;
	print_matrix(rotation_matrix, "Rotation Matrix", 4);
	return (rotation_matrix);
}