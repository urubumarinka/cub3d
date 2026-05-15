/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/05/12 13:46:30 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
	map->text.no = NULL;
	map->text.so = NULL;
	map->text.we = NULL;
	map->text.ea = NULL;
	map->text.flr_r = 0;
	map->text.flr_g = 0;
	map->text.flr_b = 0;
	map->text.flr_seen = 0;
	map->text.ceil_r = 0;
	map->text.ceil_g = 0;
	map->text.ceil_b = 0;
	map->text.ceil_seen = 0;
}

static void	set_player_direction(t_player *player, char dir)
{
	static t_direction	directions[4] = {
	{'N', 0, -1, 0.66, 0},
	{'S', 0, 1, -0.66, 0},
	{'E', 1, 0, 0, 0.66},
	{'W', -1, 0, 0, -0.66}};
	int					i;

	i = 0;
	while (i < 4)
	{
		if (directions[i].dir == dir)
		{
			player->dir_x = directions[i].dir_x;
			player->dir_y = directions[i].dir_y;
			player->plane_x = directions[i].plane_x;
			player->plane_y = directions[i].plane_y;
			return ;
		}
		i++;
	}
}

static void	init_player_dir(t_game *game, t_map *map)
{
	game->player.x = map->player_x + 0.5;
	game->player.y = map->player_y + 0.5;
	set_player_direction(&game->player, map->player_dir);
}

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
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
	game->old_time = 0;
	init_player_dir(game, &game->map);
	ft_bzero(&game->keys, sizeof(game->keys));
	if (!load_all_textures(game))
		return (0);
	return (1);
}
