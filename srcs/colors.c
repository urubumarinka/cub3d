/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:25:03 by maborges          #+#    #+#             */
/*   Updated: 2026/05/11 12:57:39 by maborges         ###   ########.fr       */
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

static void	color_assign(char id, char **values, t_map *map)
{
	if (id == 'C')
	{
		map->text.flr_r = ft_atoi(values[0]);
		map->text.flr_g = ft_atoi(values[1]);
		map->text.flr_b = ft_atoi(values[2]);
		map->text.flr_seen = 1;
	}
	else if (id == 'C')
	{
		map->text.ceil_r = ft_atoi(values[0]);
		map->text.ceil_g = ft_atoi(values[1]);
		map->text.ceil_b = ft_atoi(values[2]);
		map->text.ceil_seen = 1;
	}
}

void	extract_colors(char *color, t_map *map)
{
	char	**values;
	int		i;
	char	id;

	id = color[0];
	color += 1;
	while (*color == ' ' || *color == '\t')
		color++;
	values = ft_split(color, ',');
	if (!values || !values[0] || !values[1] || !values[2] || values[3])
		return (free_split(values), error_msg("wrong color format", NULL));
	i = -1;
	while (values[++i])
		if (!is_valid_int(values[i]))
			return (free_split(values), error_msg("not valid int", values[i]));
	if (id == 'F' || id == 'C')
		color_assign(id, values, map);
	free_split(values);
	color_range_check(map);
	return ;
}
