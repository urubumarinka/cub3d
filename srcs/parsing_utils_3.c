/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:29:22 by maborges          #+#    #+#             */
/*   Updated: 2026/05/08 16:16:02 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	parse_map(char **lines, int map_i, t_map *map)
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
		map->grid[i] = ft_strdup(lines[map_i + i]);
		if (!map->grid[i])
			return (error_msg("malloc failed", map->grid[i]), 0);
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

char	**copy_map(t_map *map)
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

int	flood_fill(char **map, int row, int col,
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

int	check_dup(t_map *map)
{
	if (map->text.ceil_seen)
		return (error_msg("Duplicated C id", NULL), 0);
	if (map->text.flr_seen)
		return (error_msg("Duplicated F id", NULL), 0);
	return (1);
}
