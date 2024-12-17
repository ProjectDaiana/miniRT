#include "minirt.h"

int	rgb_to_int(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

t_color	create_color(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color	color_add(t_color c1, t_color c2)
{
	return (create_color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b));
}

t_color	color_multiply(t_color c, double scalar)
{
	return (create_color(c.r * scalar, c.g * scalar, c.b * scalar));
}

t_color	color_multiply_colors(t_color c1, t_color c2)
{
	return (create_color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b));
}
