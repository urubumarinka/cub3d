/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:18:30 by maborges          #+#    #+#             */
/*   Updated: 2026/04/15 10:54:56 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*insert_path(char *s)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	if ((s[i] <= 13 && s[i]) >= 9|| s[i] == 32)
		i++;
	len = ft_strlen(s + i);
	while(len > 0 && s[i + len - 1] == '\n')
		len--;
	path = ft_substr(s, i, len);
	return (path);
}

static int	lines_separator(char **lines, t_map *map)
{
	//TODO duplicated id handling
	int	i;

	i = 0;
	while (lines[i])
	{
		if (empty_line(lines[i]) || lines[i][0] == '\0')
		{
			i++;
			continue ;
		}
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
			map->text.no = insert_path(lines[i] + 3);
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
			map->text.so = insert_path(lines[i] + 3);
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
			map->text.we = insert_path(lines[i] + 3);
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
			map->text.ea = insert_path(lines[i] + 3);
		else if (lines[i][0] == 'F' || lines[i][0] == 'C')
			//TODO
		else if (lines[i][0] == '0' || lines[i][0] == '1')
			break ;
		else
			return (error_msg("Wrong Identifier"), 1);
		i++;
	}
	return (i);

}

static char	**append_line(char **lines_adr, char *line, int count)
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

static char	**read_lines(char *file)
{
	int		fd;
	char	**lines;
	char	*line;
	int		count;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCant open file\n", 2);
		return (NULL);
	}
	lines = NULL;
	line = NULL;
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if(!line)
			break;
		lines = append_line(lines, line, count);
		if (!lines)
		{
			free(lines);
			free(line);
			return (NULL);
		}
		free(line);
		count++;
	}
	close(fd);
	return (lines);
}

int		parsing(char *file, t_map *map)
{
	char	**lines;
	int		map_i;
	int		p;
	//init_game(); //init all pointers to NULL and all ints to 0
	lines = NULL;
	(void)map;
	p = 0;
	lines = read_lines(file);
	while(lines && lines[p] != NULL)
	{
		printf("%s", lines[p]);
		p++;
	}
	//extract texture lines and copy it to t_map
	map_i = lines_separator(lines, map);
	return(1);
}
