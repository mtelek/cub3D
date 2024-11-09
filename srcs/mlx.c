/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:54:56 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/09 19:55:07 by mtelek           ###   ########.fr       */
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
		return (2); //could calc it better
}

int	init_mlx(t_main *main)
{
	get_display_resolution(main);
	main->pov = main->s_width; // SETTING POV
	init_data(main);
	main->data->d_ray = malloc(sizeof(float) * (main->pov + 1));
	if (!main->data->d_ray)
		exit(1); // free and printf missing here
	main->data->mlx_ptr = mlx_init();
	if (!main->data->mlx_ptr)
		return (printf(ERR_INIT_MLX), 1);
	main->data->win_ptr = mlx_new_window(main->data->mlx_ptr, main->s_width,
			main->s_height, "cub3D");
	if (!main->data->win_ptr)
		return (printf(ERR_WINDOW), 1);
	main->data->speed = get_speed(main);
	mlx_hook(main->data->win_ptr, 2, 1L << 0, handle_key_press, main);
	mlx_hook(main->data->win_ptr, 3, 1L << 1, handle_key_release, main);
	mlx_loop_hook(main->data->mlx_ptr, update_movement, main);
	mlx_loop(main->data->mlx_ptr);
	return (0);
}
