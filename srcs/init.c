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
			player->dirX = directions[i].dirX;
			player->dirY = directions[i].dirY;
			player->planeX = directions[i].planeX;
			player->planeY = directions[i].planeY;
			return ;
		}
		i++;
	}
}

static void	init_player(t_game *game)
{
	t_player	*player;

	player = &game->player;
	player->x = game->map.player_x + 0.5;
	player->y = game->map.player_y + 0.5;
	set_player_direction(player, game->map.player_dir);
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
