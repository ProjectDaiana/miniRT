/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:29:52 by darotche          #+#    #+#             */
/*   Updated: 2023/12/01 18:35:58 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(list, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count = ft_check_format(format[++i], list, count);
			i++;
		}
		else
		{
			count += ft_putchar(format[i]);
			i++;
		}
	}
	va_end(list);
	return (count);
}

// #include <stdio.h>
// int main()
// {
// 	int num;
// 	char *str2;
// 	char *str3;
// 	char *str4;
// 	num = -17;
// 	str2 = "What's";//6
// 	str3 = "up";//2
// 	str4 = "???";//3
// 	char c = 'c';
// 	int *ptr = NULL; 
// 	// My printf
// //	ft_printf("\033[0;33m\n%s\n%s\n%s\n%s\n\033[0m", num, str2, str3, str4);
// 	int result = ft_printf("\033[0;34mHi!!!!!%d%s%s%s%c\n%p%p\n\033[0m"
// 				, num, str2, str3, str4, c, ptr, &ptr);
// 	ft_printf("\033[0;35m%d written characters\n\033[0m", result);
// 	// //Putadress
// 	// int call_adress = ft_put_adr((unsigned long)&str2);
//     // //Putadres lenght
// 	// printf("\nlength:%i\n\n", call_adress);
// 	// Original
// 	int call_adress = printf("\033[0;32mHi!!!!!%d%s%s%s%c\n%p%p\n\033[0m"
//				, num, str2, str3, str4, c, ptr, &ptr);
//      //Putadres lenght
// 	printf("\nlength:%i\n\n", call_adress);
// 	}
// // REMEMBER!!!!! Colors add 11 to the count!!!!!!!
