/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/05/07 17:32:11 by maborges         ###   ########.fr       */
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

int	init_game(t_game *game)
{
	if (!init_mlx(game))
		return (0);
	game->time = 0;
	game->oldTime = 0;
	ft_bzero(&game->keys, sizeof(game->keys));
	if (!load_all_textures(game))
		return (0);
	return (1);
}
