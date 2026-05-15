/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:29:22 by maborges          #+#    #+#             */
/*   Updated: 2026/05/13 22:53:34 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	cpy_lines_helper(t_map *map, int i)
{
	int	len;

	if (!map->grid[i])
		return (error_msg("malloc failed", map->grid[i]), 0);
	len = ft_strlen(map->grid[i]);
	if (len > 0 && map->grid[i][len - 1] == '\n')
		map->grid[i][len-- - 1] = '\0';
	if (len > map->width)
		map->width = len;
	return (1);
}

int	parse_map(char **lines, int map_i, t_map *map)
{
	int	i;
	int	count;

	count = 0;
	i = map_i -1;
	while (lines[++i])
		count++;
	map->height = count;
	map->grid = malloc(sizeof(char *) * (count + 1));
	if (!map->grid)
		return (error_msg("malloc failed", *map->grid), 0);
	i = -1;
	while (++i < count)
	{
		map->grid[i] = ft_strdup(lines[map_i + i]);
		if (!cpy_lines_helper(map, i))
			return (0);
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

int	flood_fill(char **cpy, int row, int col, t_map *map)
{
	if (row < 0 || col < 0 || row >= map->height || col >= map->width)
		return (0);
	if (cpy[row][col] == ' ')
		return (0);
	if (cpy[row][col] == '1')
		return (1);
	if (cpy[row][col] == 'V')
		return (1);
	cpy[row][col] = 'V';
	if (!flood_fill(cpy, row - 1, col, map))
		return (0);
	if (!flood_fill(cpy, row + 1, col, map))
		return (0);
	if (!flood_fill(cpy, row, col - 1, map))
		return (0);
	if (!flood_fill(cpy, row, col + 1, map))
		return (0);
	return (1);
}

int	check_missing_color(t_map *map)
{
	if (!map->text.ceil_seen)
		return (error_clean(NULL, map, "Missing C id", NULL), 0);
	if (!map->text.flr_seen)
		return (error_clean(NULL, map, "Missing F id", NULL), 0);
	return (1);
}
