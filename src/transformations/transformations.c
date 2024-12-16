#include "minirt.h"

t_matrix translation(double x, double y, double z)
{
	t_matrix translation_matrix;

	translation_matrix = create_matrix(4);
	translation_matrix.m[0][0] = 1;
	translation_matrix.m[1][1] = 1;
	translation_matrix.m[2][2] = 1;
	translation_matrix.m[3][3] = 1;
	translation_matrix.m[0][3] = x;
	translation_matrix.m[1][3] = y;
	translation_matrix.m[2][3] = z;

	return (translation_matrix);
}

t_matrix scaling(double x, double y, double z)
{
	t_matrix scaling_matrix;

	scaling_matrix = create_matrix(4);
	scaling_matrix.m[0][0] = x;
	scaling_matrix.m[1][1] = y;
	scaling_matrix.m[2][2] = z;
	scaling_matrix.m[3][3] = 1;
	print_matrix(scaling_matrix, "Scaling Matrix", 4);
	return (scaling_matrix);
}

t_matrix skewing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y)
{
	t_matrix skew_matrix;

	skew_matrix = create_matrix(4);
	skew_matrix.m[0][0] = 1;
	skew_matrix.m[0][1] = x_y;
	skew_matrix.m[0][2] = x_z;
	skew_matrix.m[1][0] = y_x;
	skew_matrix.m[1][1] = 1;
	skew_matrix.m[1][2] = y_z;
	skew_matrix.m[2][0] = z_x;
	skew_matrix.m[2][1] = z_y;
	skew_matrix.m[2][2] = 1;
	skew_matrix.m[3][3] = 1;
	print_matrix(skew_matrix, "Skew Matrix", 4);
	return (skew_matrix);
}

