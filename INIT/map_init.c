/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:56:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/20 12:53:57 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	count_column(t_main *main, int row)
{
	int	i;

	i = 0;
	while (main->map->map[row][i])
		i++;
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
	int	i;
	int	j;

	i = -1;
	while (++i < main->map->mapS)
	{
		j = -1;
		while (++j < main->map->mapS)
			mlx_pixel_put(main->data->mlx_ptr, main->data->win_ptr, x + i, y
				+ j, color);
	}
}

void	map_check_failed(t_main *main)
{
	free_function(main);
	printf(ERR_INV_MAP);
	exit(1);
}

void	draw_map(t_main *main)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	count_row(main);
	if (map_check(main) == 1)
		map_check_failed(main);
	main->map->mapS = MAP_S;
	y = -1;
	while (++y < main->map->mapY)
	{
		x = -1;
		while (++x < main->map->mapX[y])
		{
			xo = x * main->map->mapS;
			yo = y * main->map->mapS;
			if (main->map->map[y][x] == '1')
				draw_rectangle(main, xo, yo, 0xFFFFFF); // White
			else
				draw_rectangle(main, xo, yo, 0x000000); // Black
		}
	}
}
