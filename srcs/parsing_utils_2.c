/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:14:15 by maborges          #+#    #+#             */
/*   Updated: 2026/05/08 16:55:51 by maborges         ###   ########.fr       */
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
	while (s[i] && s[i] != '\n' && s[i] != '\r' && s[i] != ' ')
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	player_assigments(t_map *map, int *found, int w, int h, char c)
{
	(*found)++;
	if (*found > 1)
	{
		error_msg("multiple players", NULL);
		return (0);
	}
	map->player_x = w;
	map->player_y = h;
	map->player_dir = c;
	map->grid[h][w] = '0';
	return (1);
}

int	find_player(t_map *map)
{
	int		width;
	int		height;
	int		found;
	char	p;

	found = 0;
	height = 0;
	while (height < map->height)
	{
		width = 0;
		while (map->grid[height][width])
		{
			p = map->grid[height][width];
			if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
				if (!player_assigments(map, &found, width, height, p))
					return (0);
			width++;
		}
		height++;
	}
	if (found == 0)
		return (error_msg("no player found", NULL), 0);
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

int	validate_closed(t_map *map)
{
	char	**copy;
	int		result;

	copy = copy_map(map);
	result = flood_fill(copy, map->player_y,
			map->player_x, map->height, map->width);
	free_grid(copy, map->height);
	return (result);
}
