/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:52:00 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/17 19:03:38 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

int	is_position_wall(t_main *main, float px, float py)
{
	int	map_x;
	int	map_y;
	int	buffer;

	map_x = (int)(px / main->map->mapS);
	map_y = (int)(py / main->map->mapS);
	buffer = main->player_data->player_size / 2;
	if (map_x < 0 || map_x >= main->map->mapX[map_y] || map_y < 0
		|| map_y >= main->map->mapY)
		return (1);
	if (main->map->map[map_y][map_x] == '1' || main->map->map[(int)((py
				- buffer) / main->map->mapS)][map_x] == '1'
		|| main->map->map[(int)((py + buffer) / main->map->mapS)][map_x] == '1'
		|| main->map->map[map_y][(int)((px - buffer) / main->map->mapS)] == '1'
		|| main->map->map[map_y][(int)((px + buffer) / main->map->mapS)] == '1')
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
	int	new_pos[2] = {(int)(new_px / main->map->mapS), (int)(new_py
				/ main->map->mapS)};

	curr_x = (int)(main->player_data->px / main->map->mapS);
	curr_y = (int)(main->player_data->py / main->map->mapS);
	if (is_position_wall(main, new_px, new_py))
		return (1);
	if (is_diagonal_wall(main, curr_x, curr_y, new_pos))
		return (1);
	if (is_linear_wall(main, curr_x, curr_y, new_pos))
		return (1);
	return (0);
}

int	check_lines(char *line, int end, char **map, int i)
{
	int	k;

	k = -1;
	while (line[++k] == ' ')
		;
	if (line[k] != '1')
		return (1);
	while (line[end - 1] == ' ')
		end--;
	if (line[end - 1] != '1')
		return (1);
	k = -1;
	while (map[i][++k])
	{
		if ((map[i][k] == '0' && (map[i - 1][k] == ' ' || map[i + 1][k] == ' '))
			|| (k > 0 && map[i][k] == '0' && (map[i][k - 1] == ' ' || map[i][k
					+ 1] == ' ')))
			return (1);
	}
	return (0);
}

int	check_first_last_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (1);
	}
	return (0);
}

int	check_chars(t_main *main)
{
	char	**map;
	int		i;
	int		j;
	int		player_count;

	i = -1;
	player_count = 0;
	map = main->map->map;
	while (++i < main->map->mapY)
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
				continue ;
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W')
				return (1);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				player_count++;
		}
	}
	if (player_count != 1)
		return (1);
	return (0);
}

int	map_check(t_main *main)
{
	char	**map;
	int		i;

	i = 0;
	map = main->map->map;
	if (check_chars(main) == 1)
		return (1);
	if (check_first_last_line(map[0]) == 1)
		return (1);
	if (check_first_last_line(map[main->map->mapY - 1]) == 1)
		return (1);
	while (++i < main->map->mapY - 1)
	{
		if (check_lines(map[i], main->map->mapX[i], main->map->map, i) == 1)
			return (1);
	}
	return (0);
}
