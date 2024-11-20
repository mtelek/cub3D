/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wall_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:14:36 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/20 20:21:04 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

int	is_position_wall(t_main *main, float px, float py)
{
	int	map_x;
	int	map_y;
	int	buffer;

	map_x = (int)(px / main->map->map_s);
	map_y = (int)(py / main->map->map_s);
	buffer = main->player_data->player_size / 2;
	if ((map_x < 0 || map_x >= main->map->map_x[map_y] || map_y < 0
			|| map_y >= main->map->map_y))
		return (1);
	if (main->map->map[map_y][map_x] == '1' || main->map->map[(int)((py
				- buffer) / main->map->map_s)][map_x] == '1'
		|| main->map->map[(int)((py + buffer) / main->map->map_s)][map_x] == '1'
		|| main->map->map[map_y][(int)((px - buffer) / main->map->map_s)] == '1'
		|| main->map->map[map_y][(int)((px + buffer) /
			main->map->map_s)] == '1')
		return (1);
	return (0);
}

int	is_diagonal_wall(t_main *main, int curr_x, int curr_y, int new_pos[2])
{
	int	new_x;
	int	new_y;

	new_x = new_pos[0];
	new_y = new_pos[1];
	if (curr_x != new_x && curr_y != new_y)
	{
		if (main->map->map[curr_y][new_x] == '1'
			|| main->map->map[new_y][curr_x] == '1')
			return (1);
	}
	return (0);
}

int	is_linear_wall(t_main *main, int curr_x, int curr_y, int new_pos[2])
{
	int	new_x;
	int	new_y;

	new_x = new_pos[0];
	new_y = new_pos[1];
	if (curr_x != new_x && curr_y == new_y)
	{
		if ((curr_x < new_x && main->map->map[curr_y][curr_x + 1] == '1')
			|| (curr_x > new_x && main->map->map[curr_y][curr_x - 1] == '1'))
			return (1);
	}
	if (curr_y != new_y && curr_x == new_x)
	{
		if ((curr_y < new_y && main->map->map[curr_y + 1][curr_x] == '1')
			|| (curr_y > new_y && main->map->map[curr_y - 1][curr_x] == '1'))
			return (1);
	}
	return (0);
}

int	is_wall(t_main *main, float new_px, float new_py)
{
	int	curr_x;
	int	curr_y;
	int	new_pos[2];

	new_pos[0] = (int)(new_px / main->map->map_s);
	new_pos[1] = (int)(new_py / main->map->map_s);
	curr_x = (int)(main->player_data->px / main->map->map_s);
	curr_y = (int)(main->player_data->py / main->map->map_s);
	if (is_position_wall(main, new_px, new_py))
		return (1);
	if (is_diagonal_wall(main, curr_x, curr_y, new_pos))
		return (1);
	if (is_linear_wall(main, curr_x, curr_y, new_pos))
		return (1);
	return (0);
}
