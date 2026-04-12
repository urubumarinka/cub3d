/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:50:06 by maborges          #+#    #+#             */
/*   Updated: 2026/04/12 23:09:22 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	file_check(char *path)
{
	if(!path)
		return (0);
	while (*path)
	{
		if (*path == '.')
		{
			path++;
			if(ft_strcmp(path, "cub") == 0)
				return (1);
			else
				return (0);
		}
		path++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_map	*map;

	map = NULL;
	if (ac != 2)
		error_msg("Usage: ./cub3d <map-file.cub>");
	if (!file_check(av[1]))
		error_msg("File has wrong format or doesnt exist");
	if(!parsing(*av, map))
	{
		//destroy(&map);//TODO destroy function
		error_msg("Map failed");
	}
	return (0);
}
