/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:25:57 by darotche          #+#    #+#             */
/*   Updated: 2024/07/06 19:27:26 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_spec_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_nf(char *s1, char *s2)
{
	char	*join;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_spec_strlen(s1) + ft_spec_strlen(s2);
	join = malloc((len + 1) * sizeof(char));
	i = 0;
	if (join == 0)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = malloc(ft_spec_strlen(str1) + ft_spec_strlen(str2) + 1);
	if (!newstr)
		return (NULL);
	while (str1 && str1[i])
	{
		newstr[i] = str1[i];
		i++;
	}
	free(str1);
	str1 = NULL;
	while (*str2)
	{
		newstr[i++] = *str2;
		if (*str2++ == '\n')
			break ;
	}
	newstr[i] = '\0';
	return (newstr);
}
