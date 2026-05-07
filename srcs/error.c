/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:42:14 by maborges          #+#    #+#             */
/*   Updated: 2026/05/07 17:09:18 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_msg(char *msg, char *context)
{
	ft_putstr_fd("Error\n", 2);
	if (errno != 0)
		perror(msg);
	else
	{
		ft_putstr_fd(msg, 2);
		if (context)
			ft_putstr_fd(context, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(1);
}

static void	clean(char **lines, t_map *map)
{
	int	i;

	i = 0;
	if (lines)
	{
		while (lines[i])
		{
			free(lines[i]);
			i++;
		}
		free(lines);
	}
	i = 0;
	if (map && map->grid)
	{
		while (map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
	if (map && map->text.no)
		free(map->text.no);
	if (map && map->text.so)
		free(map->text.so);
	if (map && map->text.we)
		free(map->text.we);
	if (map && map->text.ea)
		free(map->text.ea);
	if (map)
	{
		map->text.no = NULL;
		map->text.so = NULL;
		map->text.we = NULL;
		map->text.ea = NULL;
	}
}

void	error_clean(char **lines, t_map *map, char *msg, char *context)
{
	clean(lines, map);
	error_msg(msg, context);
}

void	cleanup_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->buffer)
		free(game->buffer);
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img_ptr)
			mlx_destroy_image(game->mlx, game->textures[i].img_ptr);
		i++;
	}
	if (game->image.img_ptr)
		mlx_destroy_image(game->mlx, game->image.img_ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		//mlx_destroy_display(game->mlx); //uncomment for linux
		//free(game->mlx);
	}
}

void	free_grid(char **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}
