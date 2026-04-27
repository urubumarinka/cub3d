/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:14:15 by maborges          #+#    #+#             */
/*   Updated: 2026/04/17 20:00:16 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

 int	color_range_check(t_map *map)
 {
	if (map->text.ceil_r < 0 || map->text.ceil_r > 255
		|| map->text.ceil_g < 0 || map->text.ceil_g > 255
		|| map->text.ceil_b < 0 || map->text.ceil_b > 255)
		return (error_msg("Wrong color range", NULL), 0);
	if (map->text.flr_r < 0 || map->text.flr_r > 255
		|| map->text.flr_g < 0 || map->text.flr_g > 255
		|| map->text.flr_b < 0 || map->text.flr_b > 255)
		return (error_msg("Wrong color range", NULL), 0);
	return (1);
}

int		check_dup(t_map *map)
{
	if (map->text.ceil_seen)
		return (error_msg("Duplicated C id", NULL), 0);
	if (map->text.flr_seen)
		return (error_msg("Duplicated F id", NULL), 0);
	return (1);
}

int		is_valid_int(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (!s[i])
		return (0);
	while (s[i] && s[i] != '\n' && s[i] != '\r' && s[i] != ' ')
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}


