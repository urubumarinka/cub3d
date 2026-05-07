/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/05/07 16:52:32 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_player_dir(t_game *game, t_map *map)
{
	game->player.x = map->player_x + 0.5; //centre of spawn cell
	game->player.y = map->player_y + 0.5;
	if (map->player_dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (map->player_dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (map->player_dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (map->player_dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

void	move_forward(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x + game->player.dir_x * MOVE_SPEED;
	ny = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (game->map.grid[(int)ny][(int)game->player.x] != '1')
		game->player.y = ny;
	if (game->map.grid[(int)game->player.y][(int)nx] != '1')
		game->player.x = nx;
}

void	move_backward(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x - game->player.dir_x * MOVE_SPEED;
	ny = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (game->map.grid[(int)ny][(int)game->player.x] != '1')
		game->player.y = ny;
	if (game->map.grid[(int)game->player.y][(int)nx] != '1')
		game->player.x = nx;
}

void	move_right(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x + game->player.dir_y * MOVE_SPEED;
	ny = game->player.y - game->player.dir_x * MOVE_SPEED;
	if (game->map.grid[(int)ny][(int)game->player.x] != '1')
		game->player.y = ny;
	if (game->map.grid[(int)game->player.y][(int)nx] != '1')
		game->player.x = nx;
}

void	move_left(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x - game->player.y * MOVE_SPEED;
	ny = game->player.y + game->player.x * MOVE_SPEED;
	if (game->map.grid[(int)ny][(int)game->player.x] != '1')
		game->player.y = ny;
	if (game->map.grid[(int)game->player.y][(int)nx] != '1')
		game->player.x = nx;
}
