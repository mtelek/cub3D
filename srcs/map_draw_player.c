/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/20 21:59:32 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	init_line_vars(t_main *main, int line_x, int line_y, t_line *line)
{
	line->coords[0] = main->player_data->px;
	line->coords[1] = main->player_data->py;
	line->coords[2] = line_x;
	line->coords[3] = line_y;
	line->deltas[0] = abs(line_x - (int)main->player_data->px);
	line->deltas[1] = abs(line_y - (int)main->player_data->py);
	if (main->player_data->px < line_x)
		line->steps[0] = 1;
	else
		line->steps[0] = -1;
	if (main->player_data->py < line_y)
		line->steps[1] = 1;
	else
		line->steps[1] = -1;
	line->err = line->deltas[0] - line->deltas[1];
}

void	draw_line(t_main *main, int line_x, int line_y)
{
	t_line	line;
	int		e2;

	init_line_vars(main, line_x, line_y, &line);
	while (1)
	{
		put_pixel_to_image(main, line.coords[0], line.coords[1], PLAYER_COLOR);
		if (line.coords[0] == line.coords[2]
			&& line.coords[1] == line.coords[3])
			break ;
		e2 = line.err * 2;
		if (e2 > -line.deltas[1])
		{
			line.err -= line.deltas[1];
			line.coords[0] += line.steps[0];
		}
		if (e2 < line.deltas[0])
		{
			line.err += line.deltas[0];
			line.coords[1] += line.steps[1];
		}
	}
}

void	calc_line_x_y(t_main *main)
{
	int	line_x;
	int	line_y;

	line_x = main->player_data->px + main->player_data->pdx * 20;
	line_y = main->player_data->py + main->player_data->pdy * 20;
	draw_line(main, line_x, line_y);
}

void	draw_player(t_main *main)
{
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
	calc_line_x_y(main);
}
