/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:42:14 by maborges          #+#    #+#             */
/*   Updated: 2026/04/17 11:17:25 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_msg(char *msg, char *context)
{
	ft_putstr_fd("Error\n", 2);
	if (errno != 0)
		perror(msg);
	else
	{
		ft_putstr_fd(msg, 2);
		if (context)
			ft_putstr_fd(context, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(1);
}
