/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:48:04 by maborges          #+#    #+#             */
/*   Updated: 2026/05/11 16:24:14 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	process_texture(char *line, char **texture, int *seen)
{
	if (*seen)
		return (error_msg("Duplicated texture id", NULL), 0);
	return (set_texture_path(texture, seen, line + 3));
}

static int	process_color(char *line, t_map *map, int *seen)
{
	if (*seen)
		return (error_msg("Duplicated color id", NULL), 0);
	extract_colors(line, map);
	return (*seen = 1, 1);
}

static int	process_line(char **lines, int i, t_map *map, int *state)
{
	char	*line;

	line = lines[i];
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (process_texture(line, &map->text.no, &state[0]));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (process_texture(line, &map->text.so, &state[1]));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (process_texture(line, &map->text.we, &state[2]));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (process_texture(line, &map->text.ea, &state[3]));
	else if (line[0] == 'F')
		return (process_color(line, map, &state[4]));
	else if (line[0] == 'C')
		return (process_color(line, map, &state[5]));
	else if (line[0] == '0' || line[0] == '1')
	{
		if (state[6] == -1)
			state[6] = i;
		if (!validate_map(lines, i, map))
			return (error_clean(lines, map, "map not valid", NULL), 0);
		return (1);
	}
	return (error_msg("Wrong Identifier: ", line), 0);
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
		if (!(empty_line(lines[i]) || lines[i][0] == '\0'))
			if (!process_line(lines, i, map, state))
				return (0);
		i++;
	}
	return (state[6]);
}
