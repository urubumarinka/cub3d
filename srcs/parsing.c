/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:18:30 by maborges          #+#    #+#             */
/*   Updated: 2026/05/12 16:09:38 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_valid_line(char *line)
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

int	validate_map(char **lines, int i)
{
	int	j;

	while (lines[i])
	{
		if (empty_line(lines[i]))
		{
			j = i;
			while (lines[j])
			{
				if (!empty_line(lines[j]))
					return (0);
				j++;
			}
			return (1);
		}
		if (!is_valid_line(lines[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	**read_lines(char *file)
{
	int		fd;
	char	**lines;
	char	*line;
	int		count;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCant open file\n", 2), NULL);
	lines = NULL;
	line = NULL;
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		lines = append_line(lines, line, count);
		if (!lines)
			return (free(lines), free(line), NULL);
		free(line);
		count++;
	}
	return (close(fd), lines);
}

int	parsing(char *file, t_map *map)
{
	char	**lines;
	int		map_i;

	lines = NULL;
	lines = read_lines(file);
	if (!lines)
		return (0);
	map_i = lines_separator(lines, map);
	if (map_i < 0)
		return (free_lines(lines), error_msg("no map found", NULL), 0);
	if (!check_dup(map))
		return (free_lines(lines), 0);
	if (!path_is_valid(map))
		return (free_lines(lines), error_msg("not valid path", NULL), 0);
	if (!parse_map(lines, map_i, map))
		return (free_lines(lines), 0);
	if (lines)
		free_lines(lines);
	pad_map(map);
	if (!find_player(map) || !validate_closed(map))
		return (0);
	return (1);
}

/* //Use to print the.cub file
	int		p;
	p = 0;
	while (lines && lines[p] != NULL)
	{
		printf("%s", lines[p]);
		p++;
	} */
