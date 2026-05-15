/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_separator_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:48:04 by maborges          #+#    #+#             */
/*   Updated: 2026/05/15 18:17:06 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*skip_ws(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

int	get_color_idx(char c)
{
	if (c == 'F')
		return (4);
	return (5);
}

int	check_color_format(char *rgb)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (rgb[++i])
	{
		if (rgb[i] == ',')
		{
			if (rgb[i + 1] == ',')
				return (0);
			count++;
		}
	}
	if (count != 2)
		return (0);
	return (1);
}

int	handle_map_line(char **lines, int i, t_map *map, int *state)
{
	if (state[6] == -1)
		state[6] = i;
	if (!validate_map(lines, i))
		return (error_clean(lines, map, "Invalid map", NULL), 0);
	return (1);
}

int	is_id(const char *s, const char *id)
{
	if (ft_strncmp(s, id, 2) != 0)
		return (0);
	return (s[2] == ' ' || s[2] == '\t');
}
