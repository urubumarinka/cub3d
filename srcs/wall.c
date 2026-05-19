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

static int	get_texture_index(t_game *game, double ray_dir_x, double ray_dir_y)
{
	if (game->last_side == 0)
	{
		if (ray_dir_x > 0)
			return (3);
		return (2);
	}
	if (ray_dir_y > 0)
		return (1);
	return (0);
}

static void	calculate_wall_dimensions(int *height, int *start, int *end,
	double dist)
{
	*height = (int)(SCREEN_HEIGHT / dist);
	*start = -(*height) / 2 + SCREEN_HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = (*height) / 2 + SCREEN_HEIGHT / 2;
	if (*end >= SCREEN_HEIGHT)
		*end = SCREEN_HEIGHT;
}

static void	draw_wall_column(t_game *game, int col, t_wall_render *wall)
{
	double		tex_pos;
	int			row;
	int			texture_row;
	uint32_t	color;

	tex_pos = (wall->draw_start - SCREEN_HEIGHT
			/ 2 + wall->line_height / 2) * wall->scale;
	row = wall->draw_start;
	while (row < wall->draw_end)
	{
		texture_row = (int)tex_pos % (game->textures[wall->tex_num].height);
		color = game->textures[wall->tex_num].data[texture_row
			* (game->textures[wall->tex_num].line_length / 4) + wall->tex_col];
		if (game->last_side == 1)
			color = (color / 2) & 0x7F7F7F;
		put_pixel(&game->image, col, row, color);
		tex_pos = tex_pos + wall->scale;
		row++;
	}
}

/*
draw_wall
1: Cast a ray for this screen column to find wall hit and distance.
2: Calculate wall height on screen based on distance.
3: Determine which wall texture to use and where the ray hit it.
4: Convert hit position (0-1) into a texture column (0-63). if 0.5 -> 32
tex_scale = 64 / 200 = 0.32 (advance 0.32 pixels down texture per screen pixel)
5: Draw the wall pixel by pixel using texture mapping.
*/
void	draw_wall(t_game *game, int col)
{
	double			cam_x;
	double			ray_dir_x;
	double			ray_dir_y;
	t_wall_render	wall;

	cam_x = 2 * col / (double)SCREEN_WIDTH - 1;
	ray_dir_x = game->player.dir_x + game->player.plane_x * cam_x;
	ray_dir_y = game->player.dir_y + game->player.plane_y * cam_x;
	wall.wall_dist = cast_ray(game, ray_dir_x, ray_dir_y);
	calculate_wall_dimensions(&wall.line_height, &wall.draw_start,
		&wall.draw_end, wall.wall_dist);
	wall.tex_num = get_texture_index(game, ray_dir_x, ray_dir_y);
	if (game->last_side == 0)
		wall.wall_hit_pos = game->player.y + wall.wall_dist * ray_dir_y;
	else
		wall.wall_hit_pos = game->player.x + wall.wall_dist * ray_dir_x;
	wall.wall_hit_pos = wall.wall_hit_pos - floor(wall.wall_hit_pos);
	wall.tex_col = (int)(wall.wall_hit_pos
			* game->textures[wall.tex_num].width);
	if (game->last_side == 0 && ray_dir_x > 0)
		wall.tex_col = game->textures[wall.tex_num].width - wall.tex_col - 1;
	if (game->last_side == 1 && ray_dir_y < 0)
		wall.tex_col = game->textures[wall.tex_num].width - wall.tex_col - 1;
	wall.scale = (double)game->textures[wall.tex_num].height / wall.line_height;
	draw_wall_column(game, col, &wall);
}
