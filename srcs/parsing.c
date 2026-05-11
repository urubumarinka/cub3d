/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:18:30 by maborges          #+#    #+#             */
/*   Updated: 2026/05/08 17:18:04 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	validate_map(char **lines, int i, t_map *map)
{
	int	p;

	p = 0;
	while (lines[i])
	{
		while (lines[i][p])
		{
			if (lines[i][p] != '0' && lines[i][p] != '1'
				&& lines[i][p] != 'N' && lines[i][p] != 'S'
				&& lines[i][p] != 'E' && lines[i][p] != 'W'
				&& lines[i][p] != ' ' && lines[i][p] != '\t'
				&& lines[i][p] != '\n' && lines[i][p] != '\r')
				return (0);
			p++;
		}
		i++;
	}
	(void)map; //TODO other validations
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
