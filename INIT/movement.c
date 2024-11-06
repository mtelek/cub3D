/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:22:13 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/06 20:07:08 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	update_direction(t_main *main, float angle)
{
	main->player_data->player_angle += angle;
	main->player_data->pdx = cos(main->player_data->player_angle);
	main->player_data->pdy = sin(main->player_data->player_angle);
}

int	handle_key_press(int keycode, t_main *main)
{
	if (keycode == 62307 || keycode == 65307)
	{
		mlx_destroy_window(main->data->mlx_ptr, main->data->win_ptr);
		exit(0); //needed some freeing
	}
	if (keycode == 'w')
	{
		main->data->keys[0] = 1;
		main->flag_changed = 1;
	}
	if (keycode == 'a')
	{
		main->data->keys[1] = 1;
		main->flag_changed = 1;
	}
	if (keycode == 's')
	{
		main->data->keys[2] = 1;
		main->flag_changed = 1;
	}
	if (keycode == 'd')
	{
		main->data->keys[3] = 1;
		main->flag_changed = 1;
	}
	if (keycode == 65361 || keycode == 62361)
	{
		update_direction(main, -0.1);
		main->flag_changed = 1;
	}
	if (keycode == 65363 || keycode == 62363)
	{
		update_direction(main, +0.1);
		main->flag_changed = 1;
	}
	return (0);
}

int	handle_key_release(int keycode, t_main *main)
{
	if (keycode == 'w')
		main->data->keys[0] = 0;
	if (keycode == 'a')
		main->data->keys[1] = 0;
	if (keycode == 's')
		main->data->keys[2] = 0;
	if (keycode == 'd')
		main->data->keys[3] = 0;
	return (0);
}

int	update_movement(t_main *main)
{
	float		new_px;
	float		new_py;
	static int	count;
	static int	rerender;
	
	new_px = main->player_data->px;
	new_py = main->player_data->py;
	if (main->data->keys[0])
	{
		new_px += main->player_data->pdx * main->data->speed;
		new_py += main->player_data->pdy * main->data->speed;
		main->flag_changed = 1;
	}
	if (main->data->keys[1])
	{
		new_px += main->player_data->pdy * main->data->speed;
		new_py -= main->player_data->pdx * main->data->speed;
		main->flag_changed = 1;
	}
	if (main->data->keys[2])
	{
		new_px -= main->player_data->pdx * main->data->speed;
		new_py -= main->player_data->pdy * main->data->speed;
		main->flag_changed = 1;
	}
	if (main->data->keys[3])
	{
		new_px -= main->player_data->pdy * main->data->speed;
		new_py += main->player_data->pdx * main->data->speed;
		main->flag_changed = 1;
	}
	if (!is_wall(main, new_px, new_py))
	{
		main->player_data->px = new_px;
		main->player_data->py = new_py;
	}
	if (!rerender)
	{
		render(main, count);
		rerender++;
	}
	if (main->flag_changed == 1)
	{
		render(main, count);
		count++;
		main->flag_changed = 0;
	}
	return (0);
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
