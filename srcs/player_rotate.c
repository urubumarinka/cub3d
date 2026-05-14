/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:51:44 by maborges          #+#    #+#             */
/*   Updated: 2026/05/08 12:33:41 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x
		* cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y
		* cos(ROT_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x
		* cos(ROT_SPEED) - game->player.plane_y * sin(ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y
		* cos(ROT_SPEED);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x
		* cos(-ROT_SPEED) - game->player.dir_y * sin(-ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y
		* cos(-ROT_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x
		* cos(-ROT_SPEED) - game->player.plane_y * sin(-ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y
		* cos(-ROT_SPEED);
}
