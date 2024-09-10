#include "minirt.h"

t_matrix scaling(double x, double y, double z, int w)
{
	t_matrix scaling_matrix;

	scaling_matrix = create_matrix(4);
	scaling_matrix.m[0][0] = x;
	scaling_matrix.m[1][1] = y;
	scaling_matrix.m[2][2] = z;
	scaling_matrix.m[3][3] = w;
	print_matrix(scaling_matrix, "Scaling Matrix", 4);
	return (scaling_matrix);
}

// Reflection is esenncially the same thign as scaling by a negative value
// Scenario: Reflection is scaling by a negative value
// Given transform ← scaling(-1, 1, 1)
// And p ← point(2, 3, 4)
// Then transform * p = point(-2, 3, 4)

