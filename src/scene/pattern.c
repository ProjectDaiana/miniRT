#include "minirt.h"

t_pattern create_checkers_pattern(t_color c1, t_color c2)
{
    t_pattern pattern;
    pattern.type = CHECKERS;
    pattern.color1 = c1;
    pattern.color2 = c2;
    pattern.transform = create_identity_matrix();
    return pattern;
}

t_color pattern_at_checkers(t_pattern pattern, t_tuple point)
{
    int x = floor(point.x);
    int y = floor(point.y);
    int z = floor(point.z);
    
    if ((x + y + z) % 2 == 0)
        return pattern.color1;
    else
        return pattern.color2;
}

t_color pattern_at(t_pattern pattern, t_tuple point)
{
    switch(pattern.type)
    {
        case CHECKERS:
            return pattern_at_checkers(pattern, point);
        default:
            return create_color(0, 0, 0); // Default to black
    }
}

t_color pattern_at_shape(t_pattern pattern, void *shape, t_tuple world_point)
{
    t_matrix shape_inv = inverse_matrix(&((t_plane *)shape)->transform);
    t_matrix pattern_inv = inverse_matrix(&pattern.transform);
    t_tuple object_point = matrix_multiply_tuple(shape_inv, world_point);
    t_tuple pattern_point = matrix_multiply_tuple(pattern_inv, object_point);
    return pattern_at(pattern, pattern_point);
}