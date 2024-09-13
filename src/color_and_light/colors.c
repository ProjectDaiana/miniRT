#include "minirt.h"

// int	add_color(t_color *color1, t_color *color2)
// {
// 	color1->r += color2->r;
// 	color1->g += color2->g;
// 	color1->b += color2->b;
	
// 	return rgb_to_int(*color1);
// }

// int	substract_color(t_color *color1, t_color *color2)
// {
// 	color1->r -= color2->r;
// 	color1->g -= color2->g;
// 	color1->b -= color2->b;
	
// 	return rgb_to_int(*color1);
// }

t_color	add_color(t_color color1, t_color color2)
{
	t_color	result;

	result.r = fmin(color1.r + color2.r, 255);
	result.g = fmin(color1.g + color2.g, 255);
	result.b = fmin(color1.b + color2.b, 255);
	return (result);
}

t_color substract_color(t_color color1, t_color color2)
{
	t_color	result;

	result.r = fmax(color1.r - color2.r, 0);
	result.g = fmax(color1.g - color2.g, 0);
	result.b = fmax(color1.b - color2.b, 0);
	return (result);
}

// int	multiply_color_by_scalar(t_color *color1, int scalar)
// {
// 	color1->r *= scalar;
// 	color1->g *= scalar;
// 	color1->b *= scalar;
	
// 	return rgb_to_int(*color1);
// }

t_color	multiply_color_by_scalar(t_color *color1, int scalar)
{
	color1->r *= scalar;
	color1->g *= scalar;
	color1->b *= scalar;
	
	return (*color1);
}

t_color	color_multiply(t_color a, t_color b)
{
	t_color	result;

	result.r = (a.r * b.r) / 255;
	result.g = (a.g * b.g) / 255;
	result.b = (a.b * b.b) / 255;
	return (result);
}

int	hadamard_product(t_color *color1, t_color *color2)
{
	color1->r *= color2->r;
	color1->g *= color2->g;
	color1->b *= color2->b;
	
	return rgb_to_int(*color1);
}

t_color	create_color(int r, int g, int b)
{
	return ((t_color){r, g, b});
}

t_color	scale_color(t_color color, double factor)
{
	return ((t_color){fmin(color.r * factor, 255), fmin(color.g * factor, 255),
		fmin(color.b * factor, 255)});
}
