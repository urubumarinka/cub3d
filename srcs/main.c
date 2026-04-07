/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:50:06 by maborges          #+#    #+#             */
/*   Updated: 2026/04/07 15:44:26 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	file_check(char *path)
{
	int	len;

	if(!path)
		return (0);
	len = ft_strlen(path);

	//to be continued the file name and extension check
}

int	main(int ac, char **av)
{
	t_map	*map; //TODO define struct for map in a .h file

	if (ac != 2)
		error_msg("Usage: ./cub3d <map-file.cub>");
	if (!file_check(av[1]))
		error_msg("File has wrong format or doesnt exist");
	if(!parsing(av[1]), &map); //TODO parsing function
	{
		destroy(&map);//TODO destroy function
		error_msg("Map failed");
	}
	return (0);
}
