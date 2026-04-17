/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:14:15 by maborges          #+#    #+#             */
/*   Updated: 2026/04/17 19:35:31 by maborges         ###   ########.fr       */
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
}
