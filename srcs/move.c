/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:22:13 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/19 17:22:51 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	check_wasd(int keycode, t_main *main)
{
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
}

int	handle_key_press(int keycode, t_main *main)
{
	if (keycode == 62307 || keycode == 65307)
	{
		exit_function(main);
		exit(0);
	}
	check_wasd(keycode, main);
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

void	check_keys(t_main *main, float *new_px, float *new_py)
{
	if (main->data->keys[0])
	{
		*new_px += main->player_data->pdx * main->data->speed;
		*new_py += main->player_data->pdy * main->data->speed;
		main->flag_changed = 1;
	}
	if (main->data->keys[1])
	{
		*new_px += main->player_data->pdy * main->data->speed;
		*new_py -= main->player_data->pdx * main->data->speed;
		main->flag_changed = 1;
	}
	if (main->data->keys[2])
	{
		*new_px -= main->player_data->pdx * main->data->speed;
		*new_py -= main->player_data->pdy * main->data->speed;
		main->flag_changed = 1;
	}
	if (main->data->keys[3])
	{
		*new_px -= main->player_data->pdy * main->data->speed;
		*new_py += main->player_data->pdx * main->data->speed;
		main->flag_changed = 1;
	}
}

int	update_movement(t_main *main)
{
	float		new_px;
	float		new_py;
	static int	count;
	static int	rerender;

	new_px = main->player_data->px;
	new_py = main->player_data->py;
	check_keys(main, &new_px, &new_py);
	if (rerender && !is_wall(main, new_px, new_py))
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
