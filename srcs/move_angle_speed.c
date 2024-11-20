/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_angle_speed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:21:43 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/20 20:18:42 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

float	get_speed(t_main *main)
{
	float	devide;

	devide = (float)main->s_width / (float)main->s_height;
	if (round(devide) <= 1)
		return (1.1);
	else
		return (3);
}

void	update_direction(t_main *main, float angle)
{
	main->player_data->player_angle += angle;
	main->player_data->pdx = cos(main->player_data->player_angle);
	main->player_data->pdy = sin(main->player_data->player_angle);
}

void	set_player_angle(t_main *main)
{
	if (main->player_data->direction == 'N')
		main->player_data->player_angle = 3 * M_PI / 2;
	else if (main->player_data->direction == 'S')
		main->player_data->player_angle = M_PI / 2;
	else if (main->player_data->direction == 'E')
		main->player_data->player_angle = 0;
	else if (main->player_data->direction == 'W')
		main->player_data->player_angle = M_PI;
	main->player_data->pdx = cos(main->player_data->player_angle);
	main->player_data->pdy = sin(main->player_data->player_angle);
}
