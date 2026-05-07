/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchatela <kchatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 00:00:00 by maborges          #+#    #+#             */
/*   Updated: 2026/04/27 14:55:30 by kchatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	load_texture(void *mlx, t_tex_img *texture, const char *path)
{
	texture->img_ptr = mlx_xpm_file_to_image(mlx, (char *)path,
			&texture->width, &texture->height);
	if (!texture->img_ptr)
	{
		ft_putstr_fd("Error: Failed to load texture: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(". Aborting texture initialization.\n", 2);
		return (0);
	}
	texture->data = (uint32_t *)mlx_get_data_addr(texture->img_ptr,
			&texture->bpp, &texture->line_length, &texture->endian);
	if (!texture->data)
	{
		ft_putstr_fd("Error: Failed to get texture data\n", 2);
		mlx_destroy_image(mlx, texture->img_ptr);
		texture->img_ptr = NULL;
		texture->data = NULL;
		return (0);
	}
	return (1);
}

int	load_all_textures(t_game *game)
{
	if (!load_texture(game->mlx, &game->textures[0], game->map.text.no))
		return (0);
	if (!load_texture(game->mlx, &game->textures[1], game->map.text.so))
		return (0);
	if (!load_texture(game->mlx, &game->textures[2], game->map.text.we))
		return (0);
	if (!load_texture(game->mlx, &game->textures[3], game->map.text.ea))
		return (0);
	return (1);
}
