/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:12:24 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/20 19:51:36 by mtelek           ###   ########.fr       */
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
	main->map->map_x[row] = i;
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
	main->map->map_y = i;
}
