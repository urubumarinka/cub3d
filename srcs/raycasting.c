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

static void init_dda_dist(t_game *game, t_dda *dda, double rayDirX, double rayDirY)
{
	// which grid square player is currently in
	dda->mapX = (int)game->player.x;
	dda->mapY = (int)game->player.y;
	if (rayDirX == 0) // goes straight, no hits with wall = infintiy number
		dda->deltaDistX = 1e30; 
	else
		dda->deltaDistX = fabs(1 / rayDirX); // spacing between vertical lines
	if (rayDirY == 0) // goes straight, no hits with wall = infintiy number
		dda->deltaDistY = 1e30; 
	else
		dda->deltaDistY = fabs(1 / rayDirY); // spacing between horizontal lines
}

// Initialize step directions and side distances
static void init_dda_steps(t_game *game, t_dda *dda, double rayDirX, double rayDirY)
{
	if (rayDirX < 0) // ray goes left
	{
		dda->stepX = -1;
		dda->sideDistX = (game->player.x - dda->mapX) * dda->deltaDistX;
	}
	else
	{
		dda->stepX = 1; // ray goes right
		dda->sideDistX = (dda->mapX + 1.0 - game->player.x) * dda->deltaDistX;
	}
	
	if (rayDirY < 0) //ray goes up
	{
		dda->stepY = -1;
		dda->sideDistY = (game->player.y - dda->mapY) * dda->deltaDistY;
	}
	else
	{
		dda->stepY = 1; // ray goes down
		dda->sideDistY = (dda->mapY + 1.0 - game->player.y) * dda->deltaDistY;
	}
}

//DDA init
static void init_dda(t_game *game, t_dda *dda, double rayDirX, double rayDirY)
{
	init_dda_dist(game, dda, rayDirX, rayDirY);
	init_dda_steps(game, dda, rayDirX, rayDirY);
}

// DDA logic
double dda_loop(t_game *game, t_dda *dda)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (dda->sideDistX < dda->sideDistY) // if vertical line is closer 
		{
			dda->sideDistX = dda->sideDistX + dda->deltaDistX;
			dda->mapX += dda->stepX;
			dda->side = 0;
		}
		else
		{
			dda->sideDistY += dda->deltaDistY;
			dda->mapY += dda->stepY;
			dda->side = 1;
		}
		// Check bounds and wall using parsed map
		if (dda->mapX < 0 || dda->mapX >= game->map.width || dda->mapY < 0 || dda->mapY >= game->map.height)
		{
			// Out of bounds - treat as wall
			hit = 1;
		}
		else if (game->map.grid[dda->mapY][dda->mapX] == '1')
		{
			hit = 1;
		}
	}
	if (dda->side == 0)
		return (dda->sideDistX - dda->deltaDistX);
	else
		return (dda->sideDistY - dda->deltaDistY);
}

// Calculate distance to wall
double cast_ray(t_game *game, double rayDirX, double rayDirY)
{
	// Digital Differential Analyzer : raycating algorithm
	t_dda dda;
	double wallDist;

	// init ray infos needed
	init_dda(game, &dda, rayDirX, rayDirY);
	wallDist = dda_loop(game, &dda);
	// store values for rendering
	game->lastSide = dda.side;
	game->lastMapX = dda.mapX;
	game->lastMapY = dda.mapY;
	return (wallDist);
}
