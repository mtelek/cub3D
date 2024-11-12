/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalerii <bvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:11:34 by bvalerii          #+#    #+#             */
/*   Updated: 2024/11/12 12:33:52 by bvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../Headers/cub3D.h"

int	get_x_offset_and_texture(t_main *main, t_ray *ray, t_text **t)
{
	if (ray->edge == 'V')
	{
		if (main->player_data->px < ray->hit_rx
		&&
			main->map->map[(int)(ray->hit_ry / main->map->mapS)][(int)(ray->hit_rx / main->map->mapS) - 1 ] == '0')
				*t = main->textures->ea;
		else
		 	*t = main->textures->we;
		return (fmod(ray->hit_ry * ((*t)->w / main->map->mapS), (*t)->w));
	}
	else if (ray->edge == 'H')
	{
		if (main->player_data->py > ray->hit_ry
		&&
			main->map->map[(int)(ray->hit_ry / main->map->mapS) + 1][(int)(ray->hit_rx / main->map->mapS)] == '0')
				*t = main->textures->no;
		else
			*t = main->textures->so;
   		 return (fmod(ray->hit_rx * ((*t)->w / main->map->mapS),(*t)->w));
	}
	return (0);
}

void    draw_vertical(t_main *main, int screen_x, t_ray *ray, t_wall wall)
{
	int	    offset_x;
	float	screen_y;
	float	text_y;
	float	text_step_y;
	t_text	*text;

	text = NULL;
	offset_x = get_x_offset_and_texture(main,ray, &text);

	screen_y = wall.top;
	text_y = 0;
   	text_step_y = (float)text->h / wall.height;
	while (screen_y < wall.bottom && screen_y < main->s_height)
	{
		if (text_y >= text->h)
			text_y = text->h - 1;
		put_pixel_to_image(main, screen_x, screen_y,
		text->pix[(int)text_y * text->w + offset_x]);
		screen_y++;
		text_y +=  text_step_y;
	}
}
