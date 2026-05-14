/* ************************************************************************** */
/*                                                                            */
/*                                        :::      ::::::::   */
/*   raycasting.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/04/18 00:00:00 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_dda_dist(t_game *game, t_dda *dda, double rayDirX,
	double rayDirY)
{
	dda->map_x = (int)game->player.x;
	dda->map_y = (int)game->player.y;
	if (rayDirX == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / rayDirX);
	if (rayDirY == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / rayDirY);
}

// Initialize step directions and side distances
static void	init_dda_steps(t_game *game, t_dda *dda, double rayDirX,
	double rayDirY)
{
	if (rayDirX < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (game->player.x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - game->player.x)
			* dda->delta_dist_x;
	}
	if (rayDirY < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (game->player.y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - game->player.y)
			* dda->delta_dist_y;
	}
}

static void	init_dda(t_game *game, t_dda *dda, double rayDirX, double rayDirY)
{
	init_dda_dist(game, dda, rayDirX, rayDirY);
	init_dda_steps(game, dda, rayDirX, rayDirY);
}

//Digital Differential Analyzer: raycating algorithm,calculates dist to wall
static double	dda_loop(t_game *game, t_dda *dda)
{
	while (!is_wall_hit(game, dda->map_x, dda->map_y))
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x = dda->side_dist_x + dda->delta_dist_x;
			dda->map_x = dda->map_x + dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y = dda->side_dist_y + dda->delta_dist_y;
			dda->map_y = dda->map_y + dda->step_y;
			dda->side = 1;
		}
	}
	if (dda->side == 0)
		return (dda->side_dist_x - dda->delta_dist_x);
	return (dda->side_dist_y - dda->delta_dist_y);
}

double	cast_ray(t_game *game, double rayDirX, double rayDirY)
{
	t_dda	dda;
	double	wall_dist;

	init_dda(game, &dda, rayDirX, rayDirY);
	wall_dist = dda_loop(game, &dda);
	game->last_side = dda.side;
	return (wall_dist);
}
