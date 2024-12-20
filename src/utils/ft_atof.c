/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:23:13 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 20:23:14 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_sign(const char **str, int *sign)
{
	if (**str == '-')
	{
		*sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
}

static double	get_integer_part(const char **str)
{
	double	result;

	result = 0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	get_fractional_part(const char **str)
{
	double	result;
	double	fraction;

	result = 0;
	fraction = 1.0;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			fraction *= 0.1;
			result += (**str - '0') * fraction;
			(*str)++;
		}
	}
	return (result);
}

double	ft_atof(const char *str)
{
	int		sign;
	double	result;

	sign = 1;
	handle_sign(&str, &sign);
	result = get_integer_part(&str) + get_fractional_part(&str);
	return (sign * result);
}
