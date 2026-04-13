/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:42:14 by maborges          #+#    #+#             */
/*   Updated: 2026/04/09 13:43:45 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_msg(char *msg)
{
	//printf("%s", msg);
	ft_putstr_fd("Error\n", 2);
	//clean if needed
	perror(msg);
	exit(1);
}
