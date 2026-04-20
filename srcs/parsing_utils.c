/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:59:55 by maborges          #+#    #+#             */
/*   Updated: 2026/04/20 11:51:21 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	test_file(char *path)
{
	int	fd;

	if (!path)
		return (error_msg("missing texture", NULL), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		error_msg("invalid file", path);
		return (0);
	}
	close(fd);
	return (1);
}

int	path_is_valid(t_map *map)
{
	if (!test_file(map->text.no)
		|| !test_file(map->text.so)
		|| !test_file(map->text.we)
		|| !test_file(map->text.ea))
		return (0);
	return (1);
}

char	*insert_path(char *s)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	if ((s[i] <= 13 && s[i] >= 9) || s[i] == 32)
		i++;
	len = ft_strlen(s + i);
	while (len > 0 && s[i + len - 1] == '\n')
		len--;
	path = ft_substr(s, i, len);
	return (path);
}

int	set_texture_path(char **slot, int *seen, char *line)
{
	if (*seen)
		return (error_msg("duplicate texture path", line), 0);
	*slot = insert_path(line);
	if (!*slot)
		return (error_msg("invalid texture path", line), 0);
	*seen = 1;
	return (1);
}

char	**append_line(char **lines_adr, char *line, int count)
{
	int		i;
	char	**new_arr;

	i = 0;
	new_arr = malloc(sizeof(char *) * (count + 2));
	if (!new_arr)
		return (0); //make sure the caller frees array
	while(i < count)
	{
		new_arr[i] = lines_adr[i];
		i++;
	}
	new_arr[count] = ft_strdup(line);
	if (!new_arr[count])
	{
		free(new_arr);
		return (0);
	}
	new_arr[count + 1] = NULL;
	if (lines_adr)
		free(lines_adr);
	return (new_arr);

}
