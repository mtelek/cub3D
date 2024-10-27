/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:54:56 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/27 20:44:45 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	init_keys(t_main *main)
{
	main->data->keys[0] = 0;
	main->data->keys[1] = 0;
	main->data->keys[2] = 0;
	main->data->keys[3] = 0;
}

int	init_mlx(t_main *main)
{
	get_display_resolution(main);
	init_keys(main);
	main->data->mlx_ptr = mlx_init();
	if (!main->data->mlx_ptr)
		return (printf(ERR_INIT_MLX), 1);
	main->data->win_ptr = mlx_new_window(main->data->mlx_ptr, main->s_width,
			main->s_height, "cub3D");
	if (!main->data->win_ptr)
		return (printf(ERR_WINDOW), 1);
	mlx_hook(main->data->win_ptr, 2, 1L << 0, handle_key_press, main);
	mlx_hook(main->data->win_ptr, 3, 1L << 1, handle_key_release, main);
	mlx_loop_hook(main->data->mlx_ptr, update_movement, main);
	mlx_loop(main->data->mlx_ptr);
	return (0);
}
