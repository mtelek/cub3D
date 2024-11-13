/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:54:56 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/13 20:18:54 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	init_data(t_main *main)
{
	main->data->keys[0] = 0;
	main->data->keys[1] = 0;
	main->data->keys[2] = 0;
	main->data->keys[3] = 0;
	main->data->fov = BASE_FOV * (main->s_width / main->s_height);
	main->data->angle_step = main->data->fov / main->pov;
	main->data->proj_plane_dist = main->s_width / (2 * tan(main->data->fov / 2));
}

float	get_speed(t_main *main)
{
	float devide = (float)main->s_width / (float)main->s_height;
	if (round(devide) <= 1)
		return (1.1);
	else
		return (3); //could calc it better, could use a constant here so i culd change it from .h
}

int	init_mlx(t_main *main)
{
	int hook1;
	int hook2;
	
	get_display_resolution(main);
	main->pov = main->s_width;
	init_data(main);
	main->data->d_ray = malloc(sizeof(float) * (main->pov + 1));
	if (!main->data->d_ray)
	{
		printf(ERR_MF_D_RAY);
		exit(1); // free and missing here
	}
	main->data->mlx_ptr = mlx_init();
	if (!main->data->mlx_ptr)
		return (printf(ERR_INIT_MLX), 1);
	main->data->win_ptr = mlx_new_window(main->data->mlx_ptr, main->s_width,
			main->s_height, "cub3D");
	if (!main->data->win_ptr)
		return (printf(ERR_WINDOW), 1);
	init_textures(main);
	main->data->speed = get_speed(main);
	hook1 = mlx_hook(main->data->win_ptr, 2, 1L << 0, handle_key_press, main);
	hook2 = mlx_hook(main->data->win_ptr, 3, 1L << 1, handle_key_release, main);
	if (!hook1 || !hook2)
	{
		printf(ERR_MLX_HOOK_F);
		exit (1); //proper freeing missing
	}
	if (mlx_loop_hook(main->data->mlx_ptr, update_movement, main) == 0)
	{
		printf(ERR_LOOP_HOOK);
		exit(1); //proper freeing missing
	}
	if (!main->data->mlx_ptr)
	{
		printf(ERR_NO_MLX_PTR);
		exit (1); //proper freeing missing
	}
	mlx_loop(main->data->mlx_ptr);
	return (0);
}
