/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:23:59 by maborges          #+#    #+#             */
/*   Updated: 2026/05/11 16:07:27 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	free_game_helper(t_game *game)
{
	if (game->map.grid)
	{
		free_grid(game->map.grid, game->map.height);
		game->map.grid = NULL;
	}
	if (game->map.text.no)
		free(game->map.text.no);
	if (game->map.text.so)
		free(game->map.text.so);
	if (game->map.text.we)
		free(game->map.text.we);
	if (game->map.text.ea)
		free(game->map.text.ea);
	game->map.text.no = NULL;
	game->map.text.so = NULL;
	game->map.text.we = NULL;
	game->map.text.ea = NULL;
}
