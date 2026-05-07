/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:50:06 by maborges          #+#    #+#             */
/*   Updated: 2026/05/07 16:58:41 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_map(t_map *map)
{
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

static int	file_check(char *path)
{
	if (!path)
		return (0);
	while (*path)
	{
		if (*path == '.')
		{
			path++;
			if (ft_strcmp(path, "cub") == 0)
				return (1);
			else
				return (0);
		}
		path++;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_map	map;
	t_game  game;

	ft_bzero(&map, sizeof(map));
	ft_bzero(&game, sizeof(game));
	init_map(&map);
	if (ac != 2)
		error_msg("Usage: ./cub3d <map-file.cub>", NULL);
	if (!file_check(av[1]))
		error_msg("File has wrong format or doesnt exist", NULL);
	if (!parsing(av[1], &map, &game))
		error_clean(NULL, &map, "map not valid", NULL);

	game.map = map;
	// Initialize game (creates window and initializes MLX, loads config and textures)
	if (!init_game(&game))
		return (1);
	mlx_key_hook(game.win, handle_key, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);

	// render loop - frame update: call rendering everyframe, 60 times per sec
	mlx_loop_hook(game.mlx, rendering, &game);

	// main event loop: keeps window open and responsive + listen for events
	mlx_loop(game.mlx);
	return (0);
}
