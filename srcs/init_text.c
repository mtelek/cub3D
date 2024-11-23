/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:56:57 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/23 14:12:51 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	cleanup_textures(t_data *data, t_textures *textures)
{
	if (textures->no->img)
		mlx_destroy_image(data->mlx_ptr, textures->no->img);
	if (textures->so->img)
		mlx_destroy_image(data->mlx_ptr, textures->so->img);
	if (textures->we->img)
		mlx_destroy_image(data->mlx_ptr, textures->we->img);
	if (textures->ea->img)
		mlx_destroy_image(data->mlx_ptr, textures->ea->img);
}

void	init_img(t_data *data, t_textures *textures, t_main *main)
{
	textures->no->img = mlx_xpm_file_to_image(data->mlx_ptr, textures->no->path,
			&textures->no->width, &textures->no->height);
	textures->so->img = mlx_xpm_file_to_image(data->mlx_ptr, textures->so->path,
			&textures->so->width, &textures->so->height);
	textures->we->img = mlx_xpm_file_to_image(data->mlx_ptr, textures->we->path,
			&textures->we->width, &textures->we->height);
	textures->ea->img = mlx_xpm_file_to_image(data->mlx_ptr, textures->ea->path,
			&textures->ea->width, &textures->ea->height);
	if (!textures->no->img || !textures->so->img || !textures->we->img
		|| !textures->ea->img)
	{
		printf(ERR_LOAD_TEX);
		exit_function(main, 1);
	}
}

void	init_text_data(t_textures *textures, t_main *main)
{
	textures->no->data = mlx_get_data_addr(textures->no->img,
			&textures->no->bpp, &textures->no->size_line,
			&textures->no->endian);
	textures->so->data = mlx_get_data_addr(textures->so->img,
			&textures->so->bpp, &textures->so->size_line,
			&textures->so->endian);
	textures->we->data = mlx_get_data_addr(textures->we->img,
			&textures->we->bpp, &textures->we->size_line,
			&textures->we->endian);
	textures->ea->data = mlx_get_data_addr(textures->ea->img,
			&textures->ea->bpp, &textures->ea->size_line,
			&textures->ea->endian);
	if (!textures->no->data || !textures->so->data || !textures->we->data
		|| !textures->ea->data)
	{
		printf(ERR_NO_TEX_DATA);
		exit_function(main, 1);
	}
}

void	init_textures(t_data *data, t_textures *textures, t_main *main)
{
	init_img(data, textures, main);
	init_text_data(textures, main);
	reverse_texture(textures->no, main);
	reverse_texture(textures->ea, main);
	init_floor_and_ceiling_colors(textures, main);
}
