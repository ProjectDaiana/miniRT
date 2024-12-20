/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:53:33 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 20:42:48 by tbella-n         ###   ########.fr       */
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
		fprintf(stderr, "Error: Invalid %s format\n", element);
		return (0);
	}
	return (1);
}

int	validate_coordinates(char **coords, char *element, char **to_free)
{
	if (!coords || !coords[0] || !coords[1] || !coords[2])
	{
		fprintf(stderr, "Error: Invalid %s position format\n", element);
		ft_free_split(to_free);
		return (0);
	}
	return (1);
}

int	is_valid_line(char *line)
{
	return (line[0] != '\n' && line[0] != '#' && line[0] != '\0'
		&& line[0] != ' ');
}
