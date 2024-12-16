#include "minirt.h"

double	ft_atof(const char *str)
{
	double integer_part = 0;
	double fractional_part = 0;
	double fraction = 1.0;
	int sign = 1;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	else if (*str == '+')
	{
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		integer_part = integer_part * 10 + (*str - '0');
		++str;
	}
	if (*str == '.')
	{
		++str;
		while (*str >= '0' && *str <= '9')
		{
			fraction *= 0.1;
			fractional_part += (*str - '0') * fraction;
			++str;
		}
	}
	return (sign * (integer_part + fractional_part));
}

