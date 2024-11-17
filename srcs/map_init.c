/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:56:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/17 19:05:01 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	count_column(t_main *main, int row)
{
	int	i;

	i = 0;
	while (main->map->map[row][i])
	{
		if (main->map->map[row][i] != '1' && main->map->map[row][i] != '0'
			&& main->map->map[row][i] != ' ' && row >= 1 && i >= 1)
		{
			main->player_data->py = row;
			main->player_data->px = i;
			main->player_data->direction = main->map->map[row][i];
		}
		i++;
	}
	main->map->mapX[row] = i;
}

void	count_row(t_main *main)
{
	int	i;

	i = 0;
	while (main->map->map[i])
	{
		count_column(main, i);
		i++;
	}
	main->map->mapY = i;
}

void	draw_rectangle(t_main *main, int x, int y, int color)
{
	int	screen_x;
	int	screen_y;
	int	i;
	int	j;

	i = -1;
	while (++i < main->map->mapS)
	{
		j = -1;
		while (++j < main->map->mapS)
		{
			screen_x = x + i;
			screen_y = y + j;
			put_pixel_to_image(main, screen_x, screen_y, color);
		}
	}
}

void	map_check_failed(t_main *main)
{
	free_function(main);
	printf(ERR_INV_MAP);
	exit(1);
}

int	find_biggest_x(t_main *main)
{
	int	max_x;
	int	i;
	int	row_length;

	max_x = 0;
	i = 0;
	while (main->map->map[i])
	{
		row_length = 0;
		while (main->map->map[i][row_length])
		{
			row_length++;
		}
		if (row_length > max_x)
		{
			max_x = row_length;
		}
		i++;
	}
	return (max_x);
}

void	calc_mapS(t_main *main)
{
	int	max_x;
	int	max_y;

	max_x = find_biggest_x(main);
	max_y = main->map->mapY;
	if (max_x > max_y)
		main->map->mapS = (float)main->s_width / 5.0f / (float)max_x;
	else
		main->map->mapS = (float)main->s_height / 5.0f / (float)max_y;
	main->map->mapS = round(main->map->mapS);
	main->player_data->player_size = round(main->map->mapS / 5.0f);
}

void	calc_player_pos(t_main *main)
{
	main->player_data->py = (main->player_data->py * main->map->mapS) + (0.5
			* main->map->mapS);
	main->player_data->px = (main->player_data->px * main->map->mapS) + (0.5
			* main->map->mapS);
}

void	calc_map(t_main *main)
{
	static int	count;

	if (count == 0)
	{
		count_row(main);
		calc_mapS(main);
		calc_player_pos(main);
		if (map_check(main) == 1)
			map_check_failed(main);
		count++;
	}
}

void	draw_map(t_main *main)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	y = -1;
	while (++y < main->map->mapY)
	{
		x = -1;
		while (++x < main->map->mapX[y])
		{
			xo = x * main->map->mapS;
			yo = y * main->map->mapS;
			if (main->map->map[y][x] == '1')
				draw_rectangle(main, xo, yo, COLOR_MAP_WALL);
			else
				draw_rectangle(main, xo, yo, COLOR_MAP_FLOOR);
		}
	}
}
