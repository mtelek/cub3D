/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:56:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/29 15:11:23 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void count_column(t_main *main, int row)
{
    int i;
    static int player_position_set;

    i = 0;
    while (main->map->map[row][i])
    {
        if (!player_position_set && main->map->map[row][i] != '1' && 
            main->map->map[row][i] != '0' && main->map->map[row][i] != ' ' && row >= 1 && i >= 1)
        {
            main->player_data->py = (row * main->map->mapS) + (0.5 * main->map->mapS);
            main->player_data->px = (i * main->map->mapS) + (0.5 * main->map->mapS);
			main->player_data->direction = main->map->map[row][i];
            player_position_set = 1;
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

void draw_rectangle(t_main *main, int x, int y, int color)
{
    for (int i = 0; i < main->map->mapS; i++)
    {
        for (int j = 0; j < main->map->mapS; j++)
        {
            int screen_x = x + i;
            int screen_y = y + j;
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

void	draw_map(t_main *main)
{
	int	x;
	int	y;
	int	xo;
	int	yo;

	main->map->mapS = MAP_S;
	count_row(main);
	if (map_check(main) == 1)
		map_check_failed(main);
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
