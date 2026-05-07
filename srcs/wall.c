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

void	calculate_wall_dimensions(int *height, int *start, int *end,
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
			/ 2 + (wall->draw_end - wall->draw_start) / 2) * wall->tex_scale;
	row = wall->draw_start;
	while (row < wall->draw_end)
	{
		//convert tex pos to row position on texture
		texture_row = (int)tex_pos % (game->textures[wall->tex_num].height);
		// get pixel color from texture[row][col]
		color = game->textures[wall->tex_num].data[texture_row
			* (game->textures[wall->tex_num].line_length / 4) + wall->tex_col];
		// if horiz wall, make it darker
		if (game->lastSide == 1)
			color = (color / 2) & 8355711;
		// draw pixel to screen
		put_pixel(&game->image, col, row, color);
		// move to next pos on texture
		tex_pos = tex_pos + wall->tex_scale;
		row++;
	}
}

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
    // STEP 1: Calculate WORLD coordinate where ray hit the wall
    // For vertical walls (north/south), use Y coordinate
    // For horizontal walls (east/west), use X coordinate
    // Example: player at (5.3, 7.8) + distance * direction = hit at (5.3, 10.7)
	if (game->lastSide == 0)
		wall.wall_hit_pos = game->player.y + wall.wall_dist * ray_dir_y;
	else
		wall.wall_hit_pos = game->player.x + wall.wall_dist * ray_dir_x;
    // STEP 2: Extract ONLY the fractional part to get 0-1 (within one brick)
    // Example: world coordinate 10.7 becomes 0.7 (70% across brick #10)
    // This works because each brick is 1 unit wide, and texture repeats
	wall.wall_hit_pos = wall.wall_hit_pos - floor(wall.wall_hit_pos);
    // Convert wall position (0-1) to texture column (0-63)
    // If wall_hit_pos = 0.5, and texture is 64 pixels wide:
    // tex_col = 0.5 * 64 = 32 (middle of texture)
	wall.tex_col = (int)(wall.wall_hit_pos
			* game->textures[wall.tex_num].width);
    // Flip the texture horizontally based on which direction we're looking
    // This prevents the texture from appearing mirrored
	if (game->lastSide == 0 && ray_dir_x > 0)
		wall.tex_col = game->textures[wall.tex_num].width - wall.tex_col - 1;
	if (game->lastSide == 1 && ray_dir_y < 0)
		wall.tex_col = game->textures[wall.tex_num].width - wall.tex_col - 1;
    // Calculate texture scaling ratio (how much to advance per screen pixel)
    // If texture is 64 pixels tall and wall appears 200 pixels tall on screen:
    // tex_scale = 64 / 200 = 0.32 (advance 0.32 pixels down texture per screen pixel)
	wall.tex_scale = (double)game->textures[wall.tex_num].height
			/ wall.line_height;
	draw_wall_column(game, col, &wall);
}
