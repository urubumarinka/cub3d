/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:18:30 by maborges          #+#    #+#             */
/*   Updated: 2026/04/17 16:02:02 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	lines_separator(char **lines, t_map *map)
{
	int	i;
	int	no_seen;
	int	so_seen;
	int	we_seen;
	int	ea_seen;

	i = 0;
	no_seen = 0;
	so_seen = 0;
	we_seen = 0;
	ea_seen = 0;
	while (lines[i])
	{
		if (empty_line(lines[i]) || lines[i][0] == '\0')
		{
			i++;
			continue ;
		}
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
		{
			if (!set_texture_path(&map->text.no, &no_seen, lines[i] + 3))
				return (0);
		}
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
		{
			if (!set_texture_path(&map->text.so, &so_seen, lines[i] + 3))
				return (0);
		}
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
		{
			if (!set_texture_path(&map->text.we, &we_seen, lines[i] + 3))
				return (0);
		}
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
		{
			if (!set_texture_path(&map->text.ea, &ea_seen, lines[i] + 3))
				return (0);
		}
		else if (lines[i][0] == 'F' || lines[i][0] == 'C')
			extract_colors(lines[i]); //TODO
		else if (lines[i][0] == '0' || lines[i][0] == '1')
			validate_map(); //TODO
		else
			return (error_msg("Wrong Identifier", lines[i]), 0);
		i++;
	}
	return (i);

}

static char	**read_lines(char *file)
{
	int		fd;
	char	**lines;
	char	*line;
	int		count;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCant open file\n", 2);
		return (NULL);
	}
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
		{
			free(lines);
			free(line);
			return (NULL);
		}
		free(line);
		count++;
	}
	close(fd);
	return (lines);
}

int		parsing(char *file, t_map *map)
{
	char	**lines;
	int		p;
	int		map_i;

	//init_game(); //init all pointers to NULL and all ints to 0
	lines = NULL;
	p = 0;
	lines = read_lines(file);
	while (lines && lines[p] != NULL)
	{
		printf("%s", lines[p]);
		p++;
	}
	map_i = lines_separator(lines, map);
	if (!path_is_valid(map))
		return (error_msg("not valid path", NULL), 0);
	// draw map through map_i
	return (1);
}
