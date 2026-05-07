/* ************************************************************************** */
/*                                                                            */
/*                                        :::      ::::::::   */
/*   raycasting.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/04/18 00:00:00 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// draw a single pixel at coordinates x, y on the screen
void	put_pixel(t_image *image, int x, int y, int color)
{
	int		offset;// where to write pixel
	char	*pixel;// address of pixel
	// check if pixel is outside screen
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	offset = (y * image->line_length) + (x * 4);
	pixel = image->data + offset;
	*(int *)pixel = color; // write color there
}

static void	fill_background(t_image *image, int x,
	uint32_t ceiling_color, uint32_t floor_color)
{
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		put_pixel(image, x, y, ceiling_color);
		y++;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel(image, x, y, floor_color);
		y++;
	}
}

void	draw_scene_to_screen(t_game *game)
{
	int			x;
	uint32_t	floor_color;
	uint32_t	ceiling_color;

	floor_color = (game->map.text.flr_r << 16) | (game->map.text.flr_g << 8)
		| game->map.text.flr_b;
	ceiling_color = (game->map.text.ceil_r << 16) | (game->map.text.ceil_g << 8)
		| game->map.text.ceil_b;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		fill_background(&game->image, x, ceiling_color, floor_color);
		x++;
	}
}

int	rendering(t_game *game)
{
	int	col;

	// Clear screen
	memset(game->image.data, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t)); // change to ft_
	draw_scene_to_screen(game);
	// Cast rays for each column and fill screen with wall textures
	col = 0;
	while (col < SCREEN_WIDTH)
	{
		draw_wall(game, col);
		col++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->image.img_ptr, 0, 0);
	return (0);
}
