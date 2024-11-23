/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:57:41 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/23 14:13:37 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	put_pixel_to_image(t_main *main, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < main->s_width && y >= 0 && y < main->s_height)
	{
		pixel = main->data->img_data + (y * main->data->size_line + x
				* (main->data->bpp / 8));
		*(int *)pixel = color;
	}
}

void	init_image(t_data *data, int width, int height, t_main *main)
{
	data->img = mlx_new_image(data->mlx_ptr, width, height);
	if (!data->img)
	{
		printf(ERR_NO_IMG);
		exit_function(main, 1);
	}
	data->img_data = mlx_get_data_addr(data->img, &data->bpp, &data->size_line,
			&data->endian);
	if (!data->img_data)
	{
		printf(ERR_NO_IMG_DATA_ADDRESS);
		mlx_destroy_image(main->data->mlx_ptr, main->data->img);
		exit_function(main, 1);
	}
}

void	render(t_main *main, int count)
{
	init_image(main->data, main->s_width, main->s_height, main);
	if (count == 0)
	{
		calc_map(main);
		set_player_angle(main);
	}
	draw_rays(main);
	draw_map(main);
	draw_player(main);
	if (!main->data->mlx_ptr || !main->data->win_ptr)
	{
		printf(ERR_NO_MLX_WIN_PTR);
		mlx_destroy_image(main->data->mlx_ptr, main->data->img);
		exit_function(main, 1);
	}
	mlx_put_image_to_window(main->data->mlx_ptr, main->data->win_ptr,
		main->data->img, 0, 0);
	if (!main->data->img)
	{
		printf(ERR_IMG_CREATE_F);
		mlx_destroy_image(main->data->mlx_ptr, main->data->img);
		exit_function(main, 1);
	}
	mlx_destroy_image(main->data->mlx_ptr, main->data->img);
}
