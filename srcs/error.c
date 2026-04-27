/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:42:14 by maborges          #+#    #+#             */
/*   Updated: 2026/04/27 17:31:26 by maborges         ###   ########.fr       */
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

	i = -1;
	if (lines)
	{
		while (lines[i])
			free(lines[i++]);
		free(lines);
	}
	i = -1;
	if (map->grid)
	{
		if (map->grid)
		{
			while (map->grid[i])
				free(map->grid[i++]);
			free(map->grid);
		}
	}
	if (map->text.no)
		free(map->text.no);
	if (map->text.so)
		free(map->text.so);
	if (map->text.we)
		free(map->text.we);
	if (map->text.ea)
		free(map->text.ea);

	if (map)
		free(map);
	map->text.no = NULL;
	map->text.so = NULL;
	map->text.we = NULL;
	map->text.ea = NULL;
}

void	error_clean(char **lines, t_map *map, char *msg, char*context)
{
	clean(lines, map);
	error_msg(msg, context);
}
