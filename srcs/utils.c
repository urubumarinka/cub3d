/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:53:39 by maborges          #+#    #+#             */
/*   Updated: 2026/05/15 17:38:28 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	empty_line(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] != '\0' && s[i] != '\n' && s[i] != '\t'
			&& s[i] != ' ' && s[i] != '\v' && s[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

void	free_split(char **values)

{
	int	i;

	if (!values)
		return ;
	i = 0;
	while (values[i])
	{
		free(values[i]);
		i++;
	}
	free(values);
}

void	free_grid(char **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

int	is_valid_line(char *line)
{
	int	p;

	p = 0;
	while (line[p])
	{
		if (line[p] != '0' && line[p] != '1' && line[p] != 'N'
			&& line[p] != 'S' && line[p] != 'E' && line[p] != 'W'
			&& line[p] != ' ' && line[p] != '\t' && line[p] != '\n'
			&& line[p] != '\r')
			return (0);
		p++;
	}
	return (1);
}
