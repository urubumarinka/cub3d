/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_separator_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:48:04 by maborges          #+#    #+#             */
/*   Updated: 2026/05/12 16:06:22 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*skip_ws(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

int	get_color_idx(char c)
{
	if (c == 'F')
		return (4);
	return (5);
}

int	handle_map_line(char **lines, int i, t_map *map, int *state)
{
	if (state[6] == -1)
		state[6] = i;
	return (validate_map(lines, i)
		|| (error_clean(lines, map, "map not valid", NULL), 0));
}

int	is_id(const char *s, const char *id)
{
	if (ft_strncmp(s, id, 2) != 0)
		return (0);
	return (s[2] == ' ' || s[2] == '\t');
}
