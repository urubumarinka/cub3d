/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/05/08 13:23:01 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_player_dir(t_game *game, t_map *map)
{
	game->player.x = map->player_x + 0.5;
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
