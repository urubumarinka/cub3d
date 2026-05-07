/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:18:30 by maborges          #+#    #+#             */
/*   Updated: 2026/05/07 16:59:06 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	flood_fill(char **map, int row, int col,
					int rows, int cols)
{
	if (row < 0 || col < 0 || row >= rows || col >= cols)
		return (0);
	if (map[row][col] == ' ')
		return (0);
	if (map[row][col] == '1')
		return (1);
	if (map[row][col] == 'V')
		return (1);
	map[row][col] = 'V';
	if (!flood_fill(map, row - 1, col, rows, cols))
		return (0);
	if (!flood_fill(map, row + 1, col, rows, cols))
		return (0);
	if (!flood_fill(map, row, col - 1, rows, cols))
		return (0);
	if (!flood_fill(map, row, col + 1, rows, cols))
		return (0);
	return (1);
}

static char	**copy_map(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (map->height + 1));
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->grid[i]);
		i++;
	}
	copy[map->height] = NULL;
	return (copy);
}

static int	validate_closed(t_map *map)
{
	char	**copy;
	int		result;

	copy = copy_map(map);
	result = flood_fill(copy, map->player_y,
					map->player_x, map->height, map->width);
	free_grid(copy, map->height);
	return (result);
}

static void	pad_map(t_map *map)
{
	int		row;
	int		len;
	int		pad;
	char	*padded;

	row = 0;
	while (row < map->height)
	{
		len = ft_strlen(map->grid[row]);
		if (len < map->width)
		{
			pad = map->width - len;
			padded = malloc(map->width + 1);
			ft_memcpy(padded, map->grid[row], len);
			ft_memset(padded + len, ' ', pad);
			padded[map->width] = '\0';
			free(map->grid[row]);
			map->grid[row] = padded;
		}
		row++;
	}
}

static void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

static int	find_player(t_map *map)
{
	int	width;
	int	height;
	int	found;

	found = 0;
	height = 0;
	while (height < map->height)
	{
		width = 0;
		while (map->grid[height][width])
		{
			if (map->grid[height][width] == 'N'
				|| map->grid[height][width] == 'S'
				|| map->grid[height][width] == 'E'
				|| map->grid[height][width] == 'W')
			{
				if (++found > 1)
					return (error_msg("multiple players", NULL), 0);
				map->player_x = width;
				map->player_y = height;
				map->player_dir = map->grid[height][width];
				map->grid[height][width] = '0';
			}
			width++;
		}
		height++;
	}
	if (found == 0)
		return (error_msg("no player found", NULL), 0);
	return (1);
}

static int	parse_map(char **lines, int map_i, t_map *map)
{
	int	i;
	int	count;
	int	len;

	count = 0;
	i = map_i -1;
	while (lines[++i])
		count++;
	map->grid = malloc(sizeof(char *) * (count + 1));
	if (!map->grid)
		return (error_msg("malloc failed", *map->grid), 0);
	i = -1;
	map->height = count;
	map->width = 0;
	while (++i < count)
	{
		map->grid[i] = lines[map_i + i];
		len = ft_strlen(map->grid[i]);
		if (len > 0 && map->grid[i][len - 1] == '\n')
		{
			map->grid[i][len - 1] = '\0';
			len--;
		}
		if (len > map->width)
			map->width = len;
	}
	map->grid[count] = NULL;
	return (1);
}

static int	validate_map(char **lines, int i, t_map *map)
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

static void	free_split(char **values)

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

static void	extract_colors(char *color, t_map *map)
{
	char	**values;
	int		i;
	char	id;

	id = color[0];
	color += 1;
	while (*color == ' ' || *color == '\t')
		color++;
	values = ft_split(color, ',');
	if (!values || !values[0] || !values[1] || !values[2] || values[3])
	{
		free_split(values);
		return (error_msg("wrong color format", NULL));
	}
	i = -1;
	while (values[++i])
	{
		if (!is_valid_int(values[i]))
		{
			free_split(values);
			return (error_msg("not valid int", values[i]));
		}
	}
	if (id == 'F')
	{
		map->text.flr_r = ft_atoi(values[0]);
		map->text.flr_g = ft_atoi(values[1]);
		map->text.flr_b = ft_atoi(values[2]);
		map->text.flr_seen = 1;
	}
	else if (id == 'C')
	{
		map->text.ceil_r = ft_atoi(values[0]);
		map->text.ceil_g = ft_atoi(values[1]);
		map->text.ceil_b = ft_atoi(values[2]);
		map->text.ceil_seen = 1;
	}
	free_split(values);
	color_range_check(map);
	return ;
}

static int	lines_separator(char **lines, t_map *map)
{
	int	i;
	int	no_seen;
	int	so_seen;
	int	we_seen;
	int	ea_seen;
	int	f_seen;
	int	c_seen;
	int	map_start;

	i = 0;
	map_start = -1;
	no_seen = 0;
	so_seen = 0;
	we_seen = 0;
	ea_seen = 0;
	f_seen = 0;
	c_seen = 0;
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
		else if (lines[i][0] == 'F')
		{
			if (f_seen)
				return (error_msg("Duplicated F id", NULL), 0);
			extract_colors(lines[i], map);
			f_seen = 1;
		}
		else if (lines[i][0] == 'C')
		{
			if (c_seen)
				return (error_msg("Duplicated C id", NULL), 0);
			extract_colors(lines[i], map);
			c_seen = 1;
		}
		else if (lines[i][0] == '0' || lines[i][0] == '1')
		{
			if (map_start == -1)
				map_start = i;
			if (!validate_map(lines, i, map))
				return (error_clean(lines, map, "map not valid", lines[i]), 0);
		}
		else
			return (error_msg("Wrong Identifier", lines[i]), 0);
		i++;
	}
	return (map_start);
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

int	parsing(char *file, t_map *map, t_game *game)
{
	char	**lines;
	int		map_i;

	//init_game(); //init all pointers to NULL and all ints to 0
	lines = NULL;
	lines = read_lines(file);
	map_i = lines_separator(lines, map);
	if (map_i < 0)
		return (free_lines(lines), error_msg("no map found", NULL), 0);
	if (!path_is_valid(map))
		return (free_lines(lines), error_msg("not valid path", NULL), 0);
	if (!parse_map(lines, map_i, map))
		return (free_lines(lines), 0);
	if (lines)
		free(lines);
	pad_map(map);
	if (!find_player(map) || !validate_closed(map))
		return (0);
	init_player_dir(game, map);
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
