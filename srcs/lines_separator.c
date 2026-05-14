/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:48:04 by maborges          #+#    #+#             */
/*   Updated: 2026/05/12 17:07:49 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	process_texture(char *line, char **texture, int *seen)
{
	if (*seen)
		return (0);
	return (set_texture_path(texture, seen, line + 3));
}

static int	process_color(char *line, t_map *map, int *seen)
{
	if (*seen)
		return (error_msg("Duplicated color id: ", line), 0);
	if (!check_color_format(line))
		return (error_msg("Wrong color format: ", line), 0);
	extract_colors(line, map);
	return (*seen = 1, 1);
}

static int	process_ids(char *trimmed, char **lines, t_map *map, int *st)
{
	if (is_id(trimmed, "NO"))
		return (process_texture(trimmed, &map->text.no, &st[0])
			|| (error_clean(lines, map, "Duplicated texture id", NULL), 0));
	if (is_id(trimmed, "SO"))
		return (process_texture(trimmed, &map->text.so, &st[1])
			|| (error_clean(lines, map, "Duplicated texture id", NULL), 0));
	if (is_id(trimmed, "WE"))
		return (process_texture(trimmed, &map->text.we, &st[2])
			|| (error_clean(lines, map, "Duplicated texture id", NULL), 0));
	if (is_id(trimmed, "EA"))
		return (process_texture(trimmed, &map->text.ea, &st[3])
			|| (error_clean(lines, map, "Duplicated texture id", NULL), 0));
	if ((trimmed[0] == 'F' || trimmed[0] == 'C')
		&& (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (process_color(trimmed, map, &st[get_color_idx(trimmed[0])])
			|| (error_clean(lines, map, NULL, NULL), 0));
	return (0);
}

static int	process_line(char **lines, int i, t_map *map, int *state)
{
	char	*trimmed;

	trimmed = skip_ws(lines[i]);
	if (process_ids(trimmed, lines, map, state))
		return (1);
	if (trimmed[0] == '0' || trimmed[0] == '1' || trimmed[0] == 'N'
		|| trimmed[0] == 'S' || trimmed[0] == 'E' || trimmed[0] == 'W'
		|| trimmed[0] == 'F' || trimmed[0] == 'C' || state[6] == -1)
		return (handle_map_line(lines, i, map, state));
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
