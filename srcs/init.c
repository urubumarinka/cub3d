/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/05/07 17:25:48 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!game->win)
		return (0);
	game->image.img_ptr = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->image.img_ptr)
		return (0);
	game->image.data = mlx_get_data_addr(game->image.img_ptr, &game->image.bpp,
			&game->image.line_length, &game->image.endian);
	if (!game->image.data)
		return (0);
	game->image.width = SCREEN_WIDTH;
	game->image.height = SCREEN_HEIGHT;
	return (1);
}

static void	set_player_direction(t_player *player, char dir)
{
    t_player *player = &game->player;

    // Use parsed player position from map
    player->x = game->map.player_x + 0.5;
    player->y = game->map.player_y + 0.5;

    // looking north
    player->dirX = 0;
    player->dirY = -1;

    player->planeX = 0.66;
    player->planeY = 0;
}

int	init_game(t_game *game)
{
	if (!init_mlx(game))
		return (0);
	init_player(game);
	game->time = 0;
	game->oldTime = 0;
	if (!load_all_textures(game))
		return (0);
	return (1);
}
