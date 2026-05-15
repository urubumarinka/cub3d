/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_and_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:42:14 by maborges          #+#    #+#             */
/*   Updated: 2026/05/15 17:54:49 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_msg(char *msg, char *context)
{
	int	len;

	if ((!msg || msg[0] == '\0') && errno == 0)
		return ;
	ft_putstr_fd("Error\n", 2);
	if (errno != 0)
		perror(msg);
	else
	{
		ft_putstr_fd(msg, 2);
		if (context)
		{
			len = ft_strlen(context);
			if (len > 0 && context[len - 1] == '\n')
				context[len - 1] = '\0';
			ft_putstr_fd(context, 2);
		}
		ft_putstr_fd("\n", 2);
	}
}

static void	free_map(t_map *map)
{
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

static void	clean(char **lines, t_map *map)
{
	int	i;

	i = -1;
	if (lines)
		free_lines(lines);
	if (map && map->grid)
	{
		while (map->grid[++i])
			free(map->grid[i]);
		free(map->grid);
		map->grid = NULL;
	}
	free_map(map);
}

void	error_clean(char **lines, t_map *map, char *msg, char *context)
{
	clean(lines, map);
	if (errno == EISDIR)
	{
		errno = 0;
		msg = "Not valid file, this is a dir.";
	}
	error_msg(msg, context);
	if (errno != 0)
		exit(errno);
	else
		exit(1);
}

void	cleanup_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	free_game_helper(game);
	if (game->mlx)
	{
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
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
