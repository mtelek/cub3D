/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:22:57 by bvalerii          #+#    #+#             */
/*   Updated: 2024/11/12 10:33:52 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"
#include <X11/Xlib.h>

int load_texture(void *mlx, t_text *text)
{
	text->w = TEXT_SIZE;
	text->h = TEXT_SIZE;
	text->img = mlx_xpm_file_to_image(mlx, text->path, &text->w, &text->h);
	if (!text->img || text->w != TEXT_SIZE || text->h != TEXT_SIZE)
		return (printf(ERR_INV_TEXT_IMG), printf("%s\n", text->path), 1); // do free
	text->addr = mlx_get_data_addr(text->img, &text->bpp, &text->line_l, &text->endian);
	text->pix = (int *)text->addr;
	return (0);
}

void copy_pix_line(t_text *text, char *temp_text, int y)
{
	int	x;
	int	byte;

	byte = 0;
	x = text->w - 1;
	while (x >= 0)
	{
		while (byte < (text->bpp / 8))
		{
			temp_text[y * text->line_l + (text->w - x - 1) * (text->bpp / 8) + byte]
			= text->addr[y * text->line_l + x * (text->bpp / 8) + byte];
			byte++;
		}
		byte = 0;
		x--;
	}
}

int load_texture_and_reverse(void *mlx, t_text *text)
{
	char	*temp_text;
	int		y;

	y = 0;
	if (load_texture(mlx, text))
        return (1);
	temp_text = malloc(text->line_l * text->h);
	if (!temp_text)
		return (free(temp_text), 1);
	else
		while (y < text->h)
		{
			copy_pix_line(text, temp_text, y);
			y++;
		}
	ft_memcpy(text->addr, temp_text, text->line_l * text->h);
	free(temp_text);
	return(0);
}

int load_textures(t_main *main)
{
	if (
	load_texture(main->data->mlx_ptr, main->textures->no) ||
	load_texture_and_reverse(main->data->mlx_ptr, main->textures->so)
	|| load_texture(main->data->mlx_ptr, main->textures->ea)
	|| load_texture_and_reverse(main->data->mlx_ptr, main->textures->we))
		return (1);
	return (0);
}