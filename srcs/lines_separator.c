/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:48:04 by maborges          #+#    #+#             */
/*   Updated: 2026/05/11 17:49:38 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*skip_ws(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

static int	process_texture(char *line, char **texture, int *seen)
{
	if (*seen)
		return (0);
	return (set_texture_path(texture, seen, line + 3));
}

static int	process_color(char *line, t_map *map, int *seen)
{
	if (*seen)
		return (0);
	extract_colors(line, map);
	return (*seen = 1, 1);
}

static int	process_line(char **lines, int i, t_map *map, int *state)
{
	char	*line;
	char	*trimmed;

	line = lines[i];
	trimmed = skip_ws(line);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
	{
		if (!process_texture(trimmed, &map->text.no, &state[0]))
			return (error_clean(lines, map, "Duplicated texture id", NULL), 0);
		return (1);
	}
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
	{
		if (!process_texture(trimmed, &map->text.so, &state[1]))
			return (error_clean(lines, map, "Duplicated texture id", NULL), 0);
		return (1);
	}
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
	{
		if (!process_texture(trimmed, &map->text.we, &state[2]))
			return (error_clean(lines, map, "Duplicated texture id", NULL), 0);
		return (1);
	}
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
	{
		if (!process_texture(trimmed, &map->text.ea, &state[3]))
			return (error_clean(lines, map, "Duplicated texture id", NULL), 0);
		return (1);
	}
	else if (trimmed[0] == 'F')
	{
		if (!process_color(trimmed, map, &state[4]))
			return (error_clean(lines, map, "Duplicated color id", NULL), 0);
		return (1);
	}
	else if (trimmed[0] == 'C')
	{
		if (!process_color(trimmed, map, &state[5]))
			return (error_clean(lines, map, "Duplicated color id", NULL), 0);
		return (1);
	}
	else if (trimmed[0] == '0' || trimmed[0] == '1')
	{
		if (state[6] == -1)
			state[6] = i;
		if (!validate_map(lines, i))
			return (error_clean(lines, map, "map not valid", NULL), 0);
		return (1);
	}
	return (error_clean(lines, map, "Wrong Identifier", NULL), 0);
}

int	lines_separator(char **lines, t_map *map)
{
	int	state[7];
	int	i;

	ft_memset(state, 0, sizeof(state));
	state[6] = -1;
	i = 0;
	while (lines[i])
	{
		if (!(empty_line(lines[i]) || *skip_ws(lines[i]) == '\0'))
			if (!process_line(lines, i, map, state))
				return (0);
		i++;
	}
	return (state[6]);
}
