/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:18:30 by maborges          #+#    #+#             */
/*   Updated: 2026/04/13 20:42:23 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	append_line(char ***lines_adr, char *line, int count)
{
	//input: an array of strings, the strings, how many strings
	//copy one string below another onto the array
	//return
	int		i;
	char	**new_arr;

	i = 0;
	new_arr = malloc(sizeof(char *) * (count + 2));
	if (!new_arr)
		return (0); //make sure the caller frees array
	while(i < count)
	{
		new_arr[i] = (*lines_adr)[i];
		i++;
	}
	new_arr[count] = ft_strdup(line);
	if (!new_arr[count])
	{
		free(new_arr);
		return (0);
	}
	new_arr[count + 1] = NULL;
	if (*lines_adr)
		free(*lines_adr);
	*lines_adr = new_arr;
	return (1);

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
		append_line(&lines, line, count);
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
