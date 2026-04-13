/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:18:30 by maborges          #+#    #+#             */
/*   Updated: 2026/04/12 23:18:20 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	append_line(char *lines, char *line, int count)
{
	//input: an array of strings, the strings, how many strings
	//copy one string below another onto the array
	//return
	int	i;

	i = 0;
	while(i < count)
	{
		ft_strlcpy(&lines[i], line, ft_strlen(line));
		i++;
	}
	return ;

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
		append_line(*lines, line, count);
		free(line);
		count++;
	}
	close(fd);
	return (lines);

}

int		parsing(char *file, t_map *map)
{
	char	**lines;
	int		i;
	//init_game(); //init all pointers to NULL and all ints to 0
	lines = NULL;
	(void)map;
	i = 0;
	lines = read_lines(file);
	while(lines[i] != NULL)
	{
		printf("%s", lines[i]);
		i++;
	}
	return(1);
}
