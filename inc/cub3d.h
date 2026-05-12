/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:28:04 by maborges          #+#    #+#             */
/*   Updated: 2026/05/12 13:55:44 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <errno.h>
# include "../libft/libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>
# include <string.h>

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 960
# define MOVE_SPEED 0.08
# define ROT_SPEED 0.05
# define PLAYER_RADIUS 0.20

// Linux keycodes
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

// macOS keycodes
# define MAC_KEY_W 13
# define MAC_KEY_A 0
# define MAC_KEY_S 1
# define MAC_KEY_D 2
# define MAC_KEY_LEFT 123
# define MAC_KEY_RIGHT 124
# define MAC_KEY_ESC 53

// x,y player position in map units
// dir direction vector (unit length)
// plane camera plane (perpendicular to dir)
typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_direction
{
	char	dir;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_direction;

typedef struct s_image
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_tex_img
{
	void		*img_ptr;
	uint32_t	*data;
	int			width;
	int			height;
	int			bpp;
	int			line_length;
	int			endian;
}	t_tex_img;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		flr_r;
	int		flr_g;
	int		flr_b;
	int		flr_seen;
	int		ceil_r;
	int		ceil_g;
	int		ceil_b;
	int		ceil_seen;

}	t_texture;

typedef struct s_map
{
	char		**grid;
	int			height;
	int			width;
	t_texture	text;
	int			player_x;
	int			player_y;
	char		player_dir;
}	t_map;

typedef struct s_dda
{
	int			map_x;
	int			map_y;
	double		side_dist_x;  // Distance to 1st vert grid line
	double		side_dist_y;  // Distance to 1rst hori grid line
	double		delta_dist_x; // Distance between vertical grid line always same
	double		delta_dist_y; // Dist between horizontal grid line always same
	int			step_x;          // Which dir for ray to go
	int			step_y;          // Which dir for ray to go
	int			side;
}	t_dda;

typedef struct s_wall_render
{
	double	wall_dist;
	double	wall_hit_pos;
	double	tex_scale;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	int		tex_col;
}	t_wall_render;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_game
{
	t_map		map;
	void		*mlx;
	void		*win;
	t_image		image;
	t_player	player;
	double		time;
	double		old_time;
	int			last_side;
	int			last_map_x;
	int			last_map_y;
	t_tex_img	textures[8];
	t_keys		keys;
}	t_game;

// GRAPHICS

int		init_game(t_game *game);
int		rendering(t_game *game);
int		get_wall_color(t_game *game);
int		handle_key_press(int keycode, t_game *game);
int		handle_key_release(int keycode, t_game *game);
int		close_window(t_game *game);
int		load_all_textures(t_game *game);
double	cast_ray(t_game *game, double rayDirX, double rayDirY);
void	put_pixel(t_image *image, int x, int y, int color);
void	draw_wall(t_game *game, int x);
//void	draw_minimap(t_image *image, t_game *game);

// FREES AND CLEANS

void	error_clean(char **lines, t_map *map, char *msg, char *context);
void	error_msg(char *msg, char *context);
void	cleanup_game(t_game *game);
void	error_clean(char **lines, t_map *map, char *msg, char *context);
void	free_grid(char **grid, int rows);
void	free_lines(char **lines);
void	free_game_helper(t_game *game);

// PARSING

int		parsing(char *file, t_map *map);
char	**append_line(char **lines_adr, char *line, int count);
int		set_texture_path(char **slot, int *seen, char *line);
char	*insert_path(char *s);
int		path_is_valid(t_map *map);
int		test_file(char *path);
int		color_range_check(t_map *map);
int		check_dup(t_map *map);
int		is_valid_int(char *s);
void	extract_colors(char *color, t_map *map);
void	pad_map(t_map *map);
int		find_player(t_map *map);
int		parse_map(char **lines, int map_i, t_map *map);
int		validate_closed(t_map *map);
char	**copy_map(t_map *map);
int		flood_fill(char **cpy, int row, int col, t_map *map);
int		lines_separator(char **lines, t_map *map);
int		validate_map(char **lines, int i);

// UTILS

int		empty_line(char *s);
void	free_split(char **values);

// PLAYER MOVEMENT

void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_right(t_game *game);
void	move_left(t_game *game);
void	rotate_right(t_game *game);
void	rotate_left(t_game *game);
void	update_player_movement(t_game *game);
int		can_move_x(t_game *game, double new_x, double old_y);
int		can_move_y(t_game *game, double old_x, double new_y);

#endif
