/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maborges <maborges@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:28:04 by maborges          #+#    #+#             */
/*   Updated: 2026/04/13 20:17:10 by maborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <errno.h>
#include "../libft/libft.h"
#include "../minilibx_linux/mlx.h"
#include <stdlib.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct s_player
{
    float x;
    float y;
    float angle;
    float fov; // field of view
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

typedef struct	s_map
{
	char	**grid;
	int		height;
	int		width;
	//int		player_x;
	//int		player_y;
	//char	player_dir; //as of N, S, E or W
}	t_map;

typedef struct	s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		flr_r;
	int		flr_g;
	int		flr_b;
	int		ceil_r;
	int		ceil_g;
	int		ceil_b;

}	t_texture;


typedef struct	s_game
{
	t_map		map;
	t_texture	text;
	void *mlx;
    void *win;
    t_image image;
    t_player player;
}	t_game;


void	error_msg(char *msg);
int		parsing(char *file, t_map *map);
void	error_msg(char *msg);
int		init_game(t_game *game);
int		init_graphics(t_game *game);
int		rendering(t_game *game);
void	draw_minimap(char *data, int line_length);
int		handle_key(int keycode, t_game *game);
int		close_window(t_game *game);

#endif
