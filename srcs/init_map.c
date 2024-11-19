/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:56:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/19 17:13:36 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

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

int	init_map(t_main *main)
{
	int	i;
	int	map_index;

	i = 0;
	main->map->mapX = NULL;
	while (main->content[i] && (main->content[i][0] != '0'
		&& main->content[i][0] != '1' && main->content[i][0] != ' '))
		i++;
	main->map->map = malloc(sizeof(char *) * (MAX_LINES - i));
	if (!main->map->map)
		return (printf(ERR_MF_MAP), 1);
	main->map->map[0] = NULL;
	main->map->mapX = malloc(sizeof(int) * (MAX_LINES - i));
	if (!main->map->mapX)
		return (printf(ERR_MF_MAPX), 1);
	map_index = 0;
	while (main->content[i])
	{
		main->map->map[map_index] = ft_strdup(main->content[i]);
		if (!main->map->map[map_index])
			return (printf(ERR_MF_MAP_LINE), 1);
		map_index++;
		i++;
	}
	main->map->map[map_index] = NULL;
	return (0);
}
