/* ************************************************************************** */
/*                                                                            */
/*                                        :::      ::::::::   */
/*   wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/04/18 00:00:00 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

extern int testMap[MAP_WIDTH][MAP_HEIGHT];

// time in millisec
double get_ticks(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}

void calculate_wall_dimensions(int *lineHeight, int *drawStart, int *drawEnd,
                               double wallDist)
{
    *lineHeight = (int)(SCREEN_HEIGHT / wallDist);
    *drawStart = -(*lineHeight) / 2 + SCREEN_HEIGHT / 2;
    if (*drawStart < 0)
        *drawStart = 0;
    *drawEnd = (*lineHeight) / 2 + SCREEN_HEIGHT / 2;
    if (*drawEnd >= SCREEN_HEIGHT)
        *drawEnd = SCREEN_HEIGHT - 1;
}

void draw_vertical_line(t_game *game, int x, double wallDist, double rayDirX, double rayDirY)
{
    int lineHeight;
    int drawStart;
    int drawEnd;
    int y;
    double wallX;
    int texX;

    calculate_wall_dimensions(&lineHeight, &drawStart, &drawEnd, wallDist);
    // texture based on wall direction
    int texNum = get_texture_index(game, rayDirX, rayDirY);
    if (game->lastSide == 0)
        wallX = game->player.y + wallDist * rayDirY;
    else
        wallX = game->player.x + wallDist * rayDirX;
    wallX -= floor(wallX);
    texX = (int)(wallX * (double)(TEX_WIDTH));
    if (game->lastSide == 0 && rayDirX > 0)
        texX = TEX_WIDTH - texX - 1;
    if (game->lastSide == 1 && rayDirY < 0)
        texX = TEX_WIDTH - texX - 1;
    double step = 1.0 * TEX_HEIGHT / lineHeight;
    double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
    y = drawStart;
    while (y < drawEnd)
    {
        int texY = (int)texPos & (TEX_HEIGHT - 1);
        texPos += step;
        uint32_t color = game->textures[texNum].data[TEX_HEIGHT * texX + texY];
        if (game->lastSide == 1)
            color = (color >> 1) & 8355711;
        game->buffer[y * SCREEN_WIDTH + x] = color;
        y++;
    }
}

void draw_wall_stripe(t_game *game, int col)
{
    double cameraX; // which point on plane are we looking at
    double rayDirX;
    double rayDirY;
    double wallDist;

    // calculate ray position and direction
    // if screen _width = 200 and col is in the middle = 100
    // cameraX = 2 * 100 / 200 - 1 = 0
    cameraX = 2 * col / (double)SCREEN_WIDTH - 1; // convert col (0 to SCREEN WIDTH) to  -1 = left, 0 = center, 1 = right
    rayDirX = game->player.dirX + game->player.planeX * cameraX;
    rayDirY = game->player.dirY + game->player.planeY * cameraX;
    // Cast ray and get distance to wall
    wallDist = cast_ray(game, rayDirX, rayDirY);
    // draw line with texture coordinates
    draw_vertical_line(game, col, wallDist, rayDirX, rayDirY);
}
