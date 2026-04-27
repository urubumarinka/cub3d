/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 00:00:00 by maborges          #+#    #+#             */
/*   Updated: 2026/04/27 14:57:46 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

extern int testMap[24][24];

#define MINIMAP_TILE_SIZE 6
#define MINIMAP_X 10
#define MINIMAP_Y 350

extern void put_pixel(t_image *image, int x, int y, int color);

void draw_minimap(t_image *image, t_game *game)
{
    int map_x;
    int map_y;
    int pixel_x;
    int pixel_y;
    int tx;
    int ty;
    int color;
    int player_px;
    int player_py;
    int px;
    int py;

    map_y = 0;
    while (map_y < 24)
    {
        map_x = 0;
        while (map_x < 24)
        {
            ty = 0;
            while (ty < MINIMAP_TILE_SIZE)
            {
                tx = 0;
                while (tx < MINIMAP_TILE_SIZE)
                {
                    pixel_x = MINIMAP_X + (map_y * MINIMAP_TILE_SIZE) + tx;
                    pixel_y = MINIMAP_Y + (map_x * MINIMAP_TILE_SIZE) + ty;
                    if (testMap[map_x][map_y])
                        color = 0x000000;
                    else
                        color = 0xFFFFFF;
                    put_pixel(image, pixel_x, pixel_y, color);
                    tx++;
                }
                ty++;
            }
            map_x++;
        }
        map_y++;
    }
    // Draw player on map
    player_px = MINIMAP_X + (int)(game->player.y * MINIMAP_TILE_SIZE);
    player_py = MINIMAP_Y + (int)(game->player.x * MINIMAP_TILE_SIZE);
    py = player_py - 2;
    while (py <= player_py + 2)
    {
        px = player_px - 2;
        while (px <= player_px + 2)
        {
            put_pixel(image, px, py, 0xFF0000);
            px++;
        }
        py++;
    }
    // Draw direction ray
    int ray_length = 20;
    int ray_end_x = player_px + (int)(game->player.dirY * ray_length);
    int ray_end_y = player_py + (int)(game->player.dirX * ray_length);
    int step_x = (ray_end_x > player_px) ? 1 : -1;
    int step_y = (ray_end_y > player_py) ? 1 : -1;
    int current_x = player_px;
    int current_y = player_py;
    while (current_x != ray_end_x || current_y != ray_end_y)
    {
        put_pixel(image, current_x, current_y, 0x000000);
        if (current_x != ray_end_x)
            current_x += step_x;
        if (current_y != ray_end_y)
            current_y += step_y;
    }
    put_pixel(image, ray_end_x, ray_end_y, 0x000000);
}
