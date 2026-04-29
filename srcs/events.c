/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/04/29 17:38:37 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


int handle_key(int keycode, t_game *game)
{
    if (keycode == 53 || keycode == 65307)
        close_window(game);

    return (0);
}

int close_window(t_game *game)
{
    if (game->image.img_ptr)
        mlx_destroy_image(game->mlx, game->image.img_ptr);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    exit(0);
    return (0);
}
