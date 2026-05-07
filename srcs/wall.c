/* ************************************************************************** */
/*                                                                            */
/*                                        :::      ::::::::   */
/*   wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 00:00:00 by kchatela          #+#    #+#             */
/*   Updated: 2026/04/29 00:00:00 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_texture_index(t_game *game, double ray_dir_x, double ray_dir_y)
{
	if (game->lastSide == 0)
	{
		if (ray_dir_x > 0)
			return (3);
		return (2);
	}
	if (ray_dir_y > 0)
		return (1);
	return (0);
}

void	calculate_wall_dimensions(int *h, int *start, int *end, double dist)
{
	*h = (int)(SCREEN_HEIGHT / dist);
	*start = -(*h) / 2 + SCREEN_HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = (*h) / 2 + SCREEN_HEIGHT / 2;
	if (*end >= SCREEN_HEIGHT)
		*end = SCREEN_HEIGHT - 1;
}

static void	render_column(t_game *g, int col, t_wall_render *w)
{
	double		tex_pos;
	int			y;
	int			ty;
	uint32_t	color;

	tex_pos = (w->draw_start - SCREEN_HEIGHT / 2 + (w->draw_end - w->draw_start) / 2) * w->step;
	y = w->draw_start;
	while (y < w->draw_end)
	{
		ty = (int)tex_pos & (g->textures[w->tex_num].height - 1);
		color = g->textures[w->tex_num].data[ty * (g->textures[w->tex_num].line_length / 4) + w->tex_x];
		if (g->lastSide == 1)
			color = (color >> 1) & 8355711;
		g->buffer[y * SCREEN_WIDTH + col] = color;
		tex_pos += w->step;
		y++;
	}
}

void	draw_wall_stripe(t_game *game, int col)
{
	double			cam_x;
	double			ray_x;
	double			ray_y;
	t_wall_render	wall;

	cam_x = 2 * col / (double)SCREEN_WIDTH - 1;
	ray_x = game->player.dir_x + game->player.plane_x * cam_x;
	ray_y = game->player.dir_y + game->player.plane_y * cam_x;
	wall.wall_dist = cast_ray(game, ray_x, ray_y);
	calculate_wall_dimensions(&wall.line_height, &wall.draw_start,
		&wall.draw_end, wall.wall_dist);
	wall.tex_num = get_texture_index(game, ray_x, ray_y);
	if (game->lastSide == 0)
		wall.wall_x = game->player.y + wall.wall_dist * ray_y;
	else
		wall.wall_x = game->player.x + wall.wall_dist * ray_x;
	wall.wall_x = wall.wall_x - floor(wall.wall_x);
	wall.tex_x = (int)(wall.wall_x * (double)(game->textures[wall.tex_num].width));
	if (game->lastSide == 0 && ray_x > 0)
		wall.tex_x = game->textures[wall.tex_num].width - wall.tex_x - 1;
	if (game->lastSide == 1 && ray_y < 0)
		wall.tex_x = game->textures[wall.tex_num].width - wall.tex_x - 1;
	wall.step = 1.0 * game->textures[wall.tex_num].height / wall.line_height;
	render_column(game, col, &wall);
}
