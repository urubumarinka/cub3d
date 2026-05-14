/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:14:15 by maborges          #+#    #+#             */
/*   Updated: 2026/05/14 16:31:57 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_valid_int(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (!s[i])
		return (0);
	while (s[i] && s[i] != '\n' && s[i] != '\r'
		&& s[i] != ' ' && s[i] != '\t')
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	find_player_helper(t_map *map, int y, int *found)
{
	int		x;
	char	p;

	x = 0;
	while (map->grid[y][x])
	{
		p = map->grid[y][x];
		if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
		{
			if (++(*found) > 1)
				return (error_clean(NULL, map, "Multiple players", NULL), 0);
			map->player_x = x;
			map->player_y = y;
			map->player_dir = p;
			map->grid[y][x] = '0';
		}
		x++;
	}
	return (1);
}

int	find_player(t_map *map)
{
	int		y;
	int		found;

	if (!map || !map->grid || map->height <= 0)
		return (error_clean(NULL, map, "Invalid map", NULL), 0);
	found = 0;
	y = 0;
	while (y < map->height)
	{
		if (!find_player_helper(map, y, &found))
			error_clean(NULL, map, NULL, NULL);
		y++;
	}
	if (found == 0)
		return (error_clean(NULL, map, "No player found", NULL), 0);
	return (1);
}

void	pad_map(t_map *map)
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

/* static void dump_copy(char **cpy, int rows)
{
	int i = -1;

	while (++i < rows)
		fprintf(stderr, "COPY[%d]: '%s'\n", i, cpy[i]);
} */

int	validate_closed(t_map *map)
{
	char	**copy;
	int		x;
	int		y;
	int		result;

	if (!map || !map->grid || map->height <= 0 || map->width <= 0)
		return (0);
	y = 0;
	while (y < map->height)
	{
		if (map->grid[y][0] == '0' || map->grid[y][map->width - 1] == '0')
			return (0);
		y++;
	}
	x = -1;
	while (++x < map->width)
		if (map->grid[0][x] == '0' || map->grid[map->height - 1][x] == '0')
			return (0);
	copy = copy_map(map);
	if (!copy)
		return (error_msg("malloc failed", NULL), 0);
	result = flood_fill(copy, map->player_y, map->player_x, map);
	free_grid(copy, map->height);
	return (result);
}
