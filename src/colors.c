#include "minirt.h"

int	rgb_to_int(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

// int	add_color(t_color *color1, t_color *color2)
// {
// 	color1->r += color2->r;
// 	color1->g += color2->g;
// 	color1->b += color2->b;
// 	return (rgb_to_int(*color1));
// }

t_color	add_color(t_color color1, t_color color2)
{
	t_color	result;

	result.r = fmin(color1.r + color2.r, 255);
	result.g = fmin(color1.g + color2.g, 255);
	result.b = fmin(color1.b + color2.b, 255);
	return (result);
}

int	substract_color(t_color *color1, t_color *color2)
{
	color1->r -= color2->r;
	color1->g -= color2->g;
	color1->b -= color2->b;
	return (rgb_to_int(*color1));
}

// int	multiply_color_by_scalar(t_color *color1, int scalar)
// {
// 	color1->r *= scalar;
// 	color1->g *= scalar;
// 	color1->b *= scalar;

// 	return (rgb_to_int(*color1));
// }

t_color	multiply_color_by_scalar(t_color color1, double scalar)
{
	t_color	result;

	result.r = fmin(color1.r * scalar, 255);
	result.g = fmin(color1.g * scalar, 255);
	result.b = fmin(color1.b * scalar, 255);
	return (result);
}

int	hadamard_product(t_color *color1, t_color *color2)
{
	color1->r *= color2->r;
	color1->g *= color2->g;
	color1->b *= color2->b;

	return (rgb_to_int(*color1));
}