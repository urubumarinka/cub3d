/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/05/08 14:57:04 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	move_left(t_game *game)
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

void	move_right(t_game *game)
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
