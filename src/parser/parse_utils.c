/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:53:33 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/31 02:33:46 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_params(char **split, int count, char *element)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	if (i < count)
	{
		printf("Error: Invalid %s format\n", element);
		return (0);
	}
	return (1);
}

int	validate_coordinates(char **coords, char *element, char **to_free)
{
	if (!coords || !coords[0] || !coords[1] || !coords[2])
	{
		printf("Error: Invalid %s position format\n", element);
		ft_free_split(to_free);
		exit(0);
	}
	return (1);
}

int	is_valid_line(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (*line != '\n' && *line != '#' && *line != '\0');
}
