/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:54:56 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/19 17:17:17 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	create_mlx_hooks(t_main *main)
{
	int	hook1;
	int	hook2;

	hook1 = mlx_hook(main->data->win_ptr, 2, 1L << 0, handle_key_press, main);
	hook2 = mlx_hook(main->data->win_ptr, 3, 1L << 1, handle_key_release, main);
	if (!hook1 || !hook2)
	{
		printf(ERR_MLX_HOOK_F);
		exit_function(main);
	}
	if (mlx_loop_hook(main->data->mlx_ptr, update_movement, main) == 0)
	{
		printf(ERR_LOOP_HOOK);
		exit_function(main);
	}
}

int	init_mlx(t_main *main)
{
	get_display_resolution(main);
	main->pov = main->s_width;
	if (init_data(main))
		return (1);
	init_textures(main->data, main->textures, main);
	create_mlx_hooks(main);
	if (!main->data->mlx_ptr)
	{
		printf(ERR_NO_MLX_PTR);
		exit_function(main);
	}
	mlx_loop(main->data->mlx_ptr);
	return (0);
}
