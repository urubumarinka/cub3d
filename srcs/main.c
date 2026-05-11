/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:50:06 by maborges          #+#    #+#             */
/*   Updated: 2026/05/08 13:48:47 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void init_map(t_map *map)
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

static int file_check(char *path)
{
    char *dot;

    if (!path)
        return (0);
    dot = ft_strrchr(path, '.');
    if (!dot || dot == path)
        return (0);
    return (ft_strcmp(dot + 1, "cub") == 0);
}

int main(int ac, char **av)
{
    t_map map;
    t_game game;

    ft_bzero(&map, sizeof(map));
    ft_bzero(&game, sizeof(game));
    init_map(&map);
    if (ac != 2)
        error_msg("Usage: ./cub3d <map-file.cub>", NULL);
    if (!file_check(av[1]))
        error_msg("File has wrong format or doesnt exist", NULL);
    if (!parsing(av[1], &map))
        error_clean(NULL, &map, "map not valid", NULL);
    game.map = map;
    if (!init_game(&game))
    {
        cleanup_game(&game);
        error_clean(NULL, &map, "Failed to initialize game", NULL);
    }
    mlx_hook(game.win, 2, 1L << 0, handle_key_press, &game);
    mlx_hook(game.win, 3, 1L << 1, handle_key_release, &game);
    mlx_hook(game.win, 17, 0, close_window, &game);
    mlx_loop_hook(game.mlx, rendering, &game);
    mlx_loop(game.mlx);
    return (0);
}
