/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/05/15 12:19:54 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	old_y;

	old_y = game->player.y;
	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (can_move_y(game, game->player.x, new_y))
		game->player.y = new_y;
	if (can_move_x(game, new_x, old_y))
		game->player.x = new_x;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	old_y;

	old_y = game->player.y;
	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (can_move_y(game, game->player.x, new_y))
		game->player.y = new_y;
	if (can_move_x(game, new_x, old_y))
		game->player.x = new_x;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	old_y;

	old_y = game->player.y;
	new_x = game->player.x + game->player.dir_y * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_x * MOVE_SPEED;
	if (can_move_y(game, game->player.x, new_y))
		game->player.y = new_y;
	if (can_move_x(game, new_x, old_y))
		game->player.x = new_x;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	old_y;

	old_y = game->player.y;
	new_x = game->player.x - game->player.dir_y * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_x * MOVE_SPEED;
	if (can_move_y(game, game->player.x, new_y))
		game->player.y = new_y;
	if (can_move_x(game, new_x, old_y))
		game->player.x = new_x;
}
