/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/05/08 13:23:14 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_wall(t_game *game, double x, double y)
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


void	move_forward(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x + game->player.dir_x * MOVE_SPEED;
	ny = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (can_move_y(game, game->player.x, ny))
		game->player.y = ny;
	if (can_move_x(game, nx, game->player.y))
		game->player.x = nx;
}

void	move_backward(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x - game->player.dir_x * MOVE_SPEED;
	ny = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (can_move_y(game, game->player.x, ny))
		game->player.y = ny;
	if (can_move_x(game, nx, game->player.y))
		game->player.x = nx;
}

void	move_right(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x + game->player.dir_y * MOVE_SPEED;
	ny = game->player.y - game->player.dir_x * MOVE_SPEED;
	if (can_move_y(game, game->player.x, ny))
		game->player.y = ny;
	if (can_move_x(game, nx, game->player.y))
		game->player.x = nx;
}

void	move_left(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x - game->player.dir_y * MOVE_SPEED;
	ny = game->player.y + game->player.dir_x * MOVE_SPEED;
	if (can_move_y(game, game->player.x, ny))
		game->player.y = ny;
	if (can_move_x(game, nx, game->player.y))
		game->player.x = nx;
}
