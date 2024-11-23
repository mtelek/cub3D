/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_map1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:09:07 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/23 14:15:33 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

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

void	calc_map_s(t_main *main)
{
	int	max_x;
	int	max_y;

	max_x = find_biggest_x(main);
	max_y = main->map->map_y;
	if (max_x > max_y)
		main->map->map_s = (float)main->s_width / 5.0f / (float)max_x;
	else
		main->map->map_s = (float)main->s_height / 5.0f / (float)max_y;
	main->map->map_s = round(main->map->map_s);
	main->player_data->player_size = round(main->map->map_s / 5.0f);
}

void	calc_player_pos(t_main *main)
{
	main->player_data->py = (main->player_data->py * main->map->map_s) + (0.5
			* main->map->map_s);
	main->player_data->px = (main->player_data->px * main->map->map_s) + (0.5
			* main->map->map_s);
}

void	map_check_failed(t_main *main)
{
	printf(ERR_INV_MAP);
	mlx_destroy_image(main->data->mlx_ptr, main->data->img);
	exit_function(main, 1);
}

void	calc_map(t_main *main)
{
	static int	count;

	if (count == 0)
	{
		count_row(main);
		calc_map_s(main);
		calc_player_pos(main);
		if (map_check(main) == 1)
			map_check_failed(main);
		count++;
	}
}
