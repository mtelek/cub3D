/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:52:00 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/20 00:11:48 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

int	check_lines(char *line, int end, char **map, int i)
{
	int	k;

	k = -1;
	if (line[0] == '0')
		return (1);
	if (line[end - 1] == '0')
		return (1);
	while (map[i][++k])
	{
		if (map[i][k] == '0' && (!map[i - 1][k] || !map[i + 1][k]))
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
		if (line[i] == '0')
			return (1);
	}
	return (0);
}

int	map_check(t_main *main)
{
	char	**map;
	int		i;

	i = 0;
	map = main->map->map;
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
