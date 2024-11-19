/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:52:00 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/19 17:15:09 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

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
