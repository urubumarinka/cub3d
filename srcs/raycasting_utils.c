/* ************************************************************************** */
/*                                                                            */
/*                                        :::      ::::::::   */
/*   raycasting_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/05/14 00:00:00 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_wall_hit(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= game->map.width || map_y < 0
		|| map_y >= game->map.height)
		return (1);
	return (game->map.grid[map_y][map_x] == '1');
}
