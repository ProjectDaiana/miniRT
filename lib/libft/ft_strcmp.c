/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:20:52 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 19:22:52 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	if (str1 == NULL || str2 == NULL)
		return (-1);
	while (str1[i] && (str1[i] == str2[i]))
		i++;
	if (str1[i] != str2[i])
		return (1);
	return (0);
}
