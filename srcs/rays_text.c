/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:26:13 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/19 17:26:54 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	copy_pix_line(t_texture *text, char *temp_text, int y)
{
	int	x;
	int	byte;
	int	temp_offset;
	int	data_offset;

	x = text->width - 1;
	while (x >= 0)
	{
		byte = 0;
		while (byte < text->bpp / 8)
		{
			temp_offset = y * text->size_line + (text->width - x - 1)
				* (text->bpp / 8) + byte;
			data_offset = y * text->size_line + x * (text->bpp / 8) + byte;
			temp_text[temp_offset] = text->data[data_offset];
			byte++;
		}
		x--;
	}
}

void	reverse_texture(t_texture *text, t_main *main)
{
	char	*temp_text;
	int		y;

	temp_text = malloc(text->size_line * text->height);
	if (!temp_text)
	{
		printf(ERR_MF_TEMP_TEXT);
		exit_function(main);
	}
	y = -1;
	while (++y < text->height)
		copy_pix_line(text, temp_text, y);
	ft_memcpy(text->data, temp_text, text->size_line * text->height);
	free(temp_text);
}

t_texture	*choose_wall_side(t_ray ray, t_main *main)
{
	t_texture	*texture;

	texture = NULL;
	if (ray.wall_side == 'N')
		texture = main->textures->no;
	else if (ray.wall_side == 'S')
		texture = main->textures->so;
	else if (ray.wall_side == 'W')
		texture = main->textures->we;
	else if (ray.wall_side == 'E')
		texture = main->textures->ea;
	return (texture);
}
