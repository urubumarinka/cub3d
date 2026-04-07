/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:32:43 by maborges          #+#    #+#             */
/*   Updated: 2025/05/16 17:20:03 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_read_file(char *stash, int fd);
static char	*extract_line(char *stash);
static char	*leftover(char *stash);
static char	*free_and_null(char **str);

static char	*ft_read_file(char *stash, int fd)
{
	char		*tmpbuff;
	int			bytes_read;
	char		*temp;

	bytes_read = 1;
	tmpbuff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!tmpbuff)
		return (free_and_null(&stash));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, tmpbuff, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (free(tmpbuff), stash);
		tmpbuff[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin(stash, tmpbuff);
		free(temp);
		if (!stash)
			return (free(tmpbuff), NULL);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	free(tmpbuff);
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*extracted_line;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	extracted_line = ft_calloc(i + 1, sizeof(char));
	if (!extracted_line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		extracted_line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		extracted_line[i++] = '\n';
	extracted_line[i] = '\0';
	return (extracted_line);
}

static char	*leftover(char *stash)
{
	char	*remaining_line;
	char	*newstash;

	remaining_line = ft_strchr(stash, '\n');
	if (remaining_line)
	{
		remaining_line += 1;
		newstash = ft_strdup(remaining_line);
		if (!newstash)
		{
			free(stash);
			return (NULL);
		}
		free(stash);
		return (newstash);
	}
	free(stash);
	return (NULL);
}

static char	*free_and_null(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*stash;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_and_null(&stash));
	if (!stash)
		stash = ft_calloc(1, sizeof(char));
	if (!stash)
		return (NULL);
	stash = ft_read_file(stash, fd);
	if (!stash || *stash == '\0')
		return (free_and_null(&stash));
	line = extract_line(stash);
	if (!line)
		return (free_and_null(&stash));
	stash = leftover(stash);
	return (line);
}
