/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/05/08 14:49:53 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_wall(t_game *game, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_x < 0 || grid_y < 0
		|| grid_x >= game->map.width || grid_y >= game->map.height)
		return (1);
	if (game->map.grid[grid_y][grid_x] == '1')
		return (1);
	return (0);
}

int	can_move_x(t_game *game, double new_x, double old_y)
{
	if (is_wall(game, new_x - PLAYER_RADIUS, old_y - PLAYER_RADIUS))
		return (0);
	if (is_wall(game, new_x - PLAYER_RADIUS, old_y + PLAYER_RADIUS))
		return (0);
	if (is_wall(game, new_x + PLAYER_RADIUS, old_y - PLAYER_RADIUS))
		return (0);
	if (is_wall(game, new_x + PLAYER_RADIUS, old_y + PLAYER_RADIUS))
		return (0);
	return (1);
}

int	can_move_y(t_game *game, double old_x, double new_y)
{
	if (is_wall(game, old_x - PLAYER_RADIUS, new_y - PLAYER_RADIUS))
		return (0);
	if (is_wall(game, old_x - PLAYER_RADIUS, new_y + PLAYER_RADIUS))
		return (0);
	if (is_wall(game, old_x + PLAYER_RADIUS, new_y - PLAYER_RADIUS))
		return (0);
	if (is_wall(game, old_x + PLAYER_RADIUS, new_y + PLAYER_RADIUS))
		return (0);
	return (1);
}
