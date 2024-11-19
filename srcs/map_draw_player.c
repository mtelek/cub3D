/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/19 18:10:22 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	draw_line_segment(t_main *main, int *coords, int *deltas, int *steps,
		int *err)
{
	int	e2;

	while (1)
	{
		put_pixel_to_image(main, coords[0], coords[1], PLAYER_COLOR);
		if (coords[0] == coords[2] && coords[1] == coords[3])
			break ;
		e2 = (*err) * 2;
		if (e2 > -deltas[1])
		{
			*err -= deltas[1];
			coords[0] += steps[0];
		}
		if (e2 < deltas[0])
		{
			*err += deltas[0];
			coords[1] += steps[1];
		}
	}
}

void	draw_line(t_main *main, int x0, int y0, int x1, int y1)
{
	int	coords[4];
	int	deltas[2];
	int	steps[2];
	int	err;

	coords[0] = x0;
	coords[1] = y0;
	coords[2] = x1;
	coords[3] = y1;
	deltas[0] = abs(x1 - x0);
	deltas[1] = abs(y1 - y0);
	if (x0 < x1)
		steps[0] = 1;
	else
		steps[0] = -1;
	if (y0 < y1)
		steps[1] = 1;
	else
		steps[1] = -1;
	err = deltas[0] - deltas[1];
	draw_line_segment(main, coords, deltas, steps, &err);
}

void	draw_player(t_main *main)
{
	int	line_x;
	int	line_y;
	int	screen_x;
	int	screen_y;
	int	x;
	int	y;

	y = -main->player_data->player_size - 1;
	while (++y <= main->player_data->player_size)
	{
		x = -main->player_data->player_size - 1;
		while (++x <= main->player_data->player_size)
		{
			screen_x = main->player_data->px + x;
			screen_y = main->player_data->py + y;
			if (screen_x >= 0 && screen_x < main->s_width && screen_y >= 0
				&& screen_y < main->s_height)
				put_pixel_to_image(main, screen_x, screen_y, PLAYER_COLOR);
		}
	}
	line_x = main->player_data->px + main->player_data->pdx * 20;
	line_y = main->player_data->py + main->player_data->pdy * 20;
	draw_line(main, main->player_data->px, main->player_data->py, line_x,
		line_y);
}
