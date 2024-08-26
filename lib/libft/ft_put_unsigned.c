/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:15:14 by darotche          #+#    #+#             */
/*   Updated: 2023/12/01 18:36:19 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_unsigned(unsigned int n)
{
	int			len;

	len = 0;
	if (n >= 10)
	{
		len += ft_putnbr(n / 10);
		len += ft_putnbr(n % 10);
	}
	if (n < 10)
		len += ft_putchar(n + '0');
	return (len);
}
