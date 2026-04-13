/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:50:06 by maborges          #+#    #+#             */
/*   Updated: 2026/04/06 16:55:08 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int main(int ac, char **av)
{
    t_game game;

    (void)av;
    if (ac != 2)
        printf("Error");

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
