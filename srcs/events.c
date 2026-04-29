/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/04/27 14:49:07 by kchatela         ###   ########.fr       */
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
	cleanup_game(game);
	exit(0);
	return (0);
}