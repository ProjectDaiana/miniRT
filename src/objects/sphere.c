#include "minirt.h"

t_material default_material() {
    t_material mat = {0.1, 0.9, 0.9, 200.0};  // Example material properties
	return mat;
}


t_tuple point(double x, double y, double z) {
    return (t_tuple){x, y, z, 1.0};  // Assuming w = 1 for points
}

t_sphere sphere()
{
    t_sphere s;
    s.center = point(0, 0, 0);           // Default center at the origin
    s.material = default_material();     // Default material
    s.radius = 1.0;                      // Default radius of 1
    return s;
}

