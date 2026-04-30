/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/04/27 17:40:34 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int init_graphics(t_game *game)
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
    game->image.data = mlx_get_data_addr(game->image.img_ptr, &game->image.bpp, &game->image.line_length, &game->image.endian);
    if (!game->image.data)
        return (0);
    game->image.width = SCREEN_WIDTH;
    game->image.height = SCREEN_HEIGHT;
    return (1);
}

void init_player(t_game *game)
{
    t_player *player = &game->player;

    player->x = game->map.player_x + 0.5;
    player->y = game->map.player_y + 0.5;
    if (game->map.player_dir == 'N')
    {
        player->dirX = 0;
        player->dirY = -1;
        player->planeX = 0.66;
        player->planeY = 0;
    }
    else if (game->map.player_dir == 'S')
    {
        player->dirX = 0;
        player->dirY = 1;
        player->planeX = -0.66;
        player->planeY = 0;
    }
    else if (game->map.player_dir == 'E')
    {
        player->dirX = 1;
        player->dirY = 0;
        player->planeX = 0;
        player->planeY = 0.66;
    }
    else if (game->map.player_dir == 'W')
    {
        player->dirX = -1;
        player->dirY = 0;
        player->planeX = 0;
        player->planeY = -0.66;
    }
}

int init_game(t_game *game)
{
    // Allocate screen buffer
    game->buffer = (uint32_t *)malloc(SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
    if (!game->buffer)
        return (0);
    if (!init_graphics(game))
        return (0);
    init_player(game);
    game->time = 0;
    game->oldTime = 0;
    if (!load_all_textures(game))
        return (0);
    return (1);
}