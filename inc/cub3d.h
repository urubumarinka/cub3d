/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:28:04 by maborges          #+#    #+#             */
/*   Updated: 2026/04/27 18:14:03 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <errno.h>
#include "../libft/libft.h"
#include "../minilibx_linux/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960
#define CEILING_COLOR 0xFF0000 // red
#define FLOOR_COLOR 0x000000   // black

#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

typedef struct s_player
{
    double x;
    double y;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
} t_player;

typedef struct s_image
{
    void *img_ptr;
    char *data;
    int bpp;
    int line_length;
    int endian;
    int width;
    int height;
} t_image;

typedef struct s_tex_img
{
    void *img_ptr;
    uint32_t *data;
    int width;
    int height;
    int bpp;
    int line_length;
    int endian;
} t_tex_img;

typedef struct s_texture
{
    char *no;
    char *so;
    char *we;
    char *ea;
    int flr_r;
    int flr_g;
    int flr_b;
    int	flr_seen;
    int ceil_r;
    int ceil_g;
    int ceil_b;
    int	ceil_seen;

} t_texture;

typedef struct s_map
{
    char **grid;
    int height;
    int width;
    t_texture text;
    int		player_x;
    int		player_y;
    char	player_dir; //as of N, S, E or W
} t_map;

typedef struct s_dda
{
    int mapX;
    int mapY;
    double sideDistX; // Distance to 1st vert grid line
    double sideDistY; // Distance to 1rst hori grid line
    double deltaDistX; // Distance between vertical grid line always same
    double deltaDistY; // Distance between horizontal grid line always same
    int stepX; // Which dir for ray to go
    int stepY; // Which dir for ray to go 
    int side;
} t_dda;

typedef struct s_game
{
    t_map map;
    t_texture text;
    void *mlx;
    void *win;
    t_image image;
    t_player player;
    double time;
    double oldTime;
    int lastSide;
    int lastMapX;
    int lastMapY;
    uint32_t *buffer;      // uint32_t cause we storing 32-bit color values in the buffer
    t_tex_img textures[8];
} t_game;

void error_msg(char *msg, char *context);
int init_game(t_game *game);
int init_graphics(t_game *game);
void init_player(t_player *player);
double get_ticks(void);
void put_pixel(t_image *image, int x, int y, int color);

int rendering(t_game *game);
void draw_scene_to_buffer(uint32_t *buffer);
void draw_wall_stripe(t_game *game, int x);
void draw_vertical_line(t_game *game, int x, double wallDist, double rayDirX, double rayDirY);
double cast_ray(t_game *game, double rayDirX, double rayDirY);
double dda_loop(t_dda *dda);
int get_wall_color(t_game *game);
void calculate_wall_dimensions(int *lineHeight, int *drawStart, int *drawEnd,
                               double wallDist);
void draw_minimap(t_image *image, t_game *game);
int handle_key(int keycode, t_game *game);
int close_window(t_game *game);
void load_config(t_game *game);
void load_config_textures(t_game *game);
int get_texture_index(t_game *game, double rayDirX, double rayDirY);
int load_texture(void *mlx, t_tex_img *texture, const char *path);
int load_all_textures(t_game *game);


void	error_clean(char **lines, t_map *map, char *msg, char*context);

//parsing

int		parsing(char *file, t_map *map);
char	**append_line(char **lines_adr, char *line, int count);
int		set_texture_path(char **slot, int *seen, char *line);
char	*insert_path(char *s);
int		path_is_valid(t_map *map);
int		test_file(char *path);
int		color_range_check(t_map *map);
int		check_dup(t_map *map);
int		is_valid_int(char *s);

//utils

int		empty_line(char *s);


#endif
