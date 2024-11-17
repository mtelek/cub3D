/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:57:41 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/17 21:46:33 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	draw_line_segment(t_main *main, int *coords, int *deltas, int *steps,
		int *err)
{
	int	e2;

	while (1)
	{
		put_pixel_to_image(main, coords[0], coords[1], PLAYER_COLOR);
		if (coords[0] == coords[2] && coords[1] == coords[3])
			break ;
		e2 = (*err) * 2;
		if (e2 > -deltas[1])
		{
			*err -= deltas[1];
			coords[0] += steps[0];
		}
		if (e2 < deltas[0])
		{
			*err += deltas[0];
			coords[1] += steps[1];
		}
	}
}

void	draw_line(t_main *main, int x0, int y0, int x1, int y1)
{
	int	coords[4];
	int	deltas[2];
	int	steps[2];
	int	err;

	coords[0] = x0;
	coords[1] = y0;
	coords[2] = x1;
	coords[3] = y1;
	deltas[0] = abs(x1 - x0);
	deltas[1] = abs(y1 - y0);
	if (x0 < x1)
		steps[0] = 1;
	else
		steps[0] = -1;
	if (y0 < y1)
		steps[1] = 1;
	else
		steps[1] = -1;
	err = deltas[0] - deltas[1];
	draw_line_segment(main, coords, deltas, steps, &err);
}

void	draw_player(t_main *main)
{
	int	line_x;
	int	line_y;
	int	screen_x;
	int	screen_y;
	int	x;
	int	y;

	y = -main->player_data->player_size - 1;
	while (++y <= main->player_data->player_size)
	{
		x = -main->player_data->player_size - 1;
		while (++x <= main->player_data->player_size)
		{
			screen_x = main->player_data->px + x;
			screen_y = main->player_data->py + y;
			if (screen_x >= 0 && screen_x < main->s_width && screen_y >= 0
				&& screen_y < main->s_height)
				put_pixel_to_image(main, screen_x, screen_y, PLAYER_COLOR);
		}
	}
	line_x = main->player_data->px + main->player_data->pdx * 20;
	line_y = main->player_data->py + main->player_data->pdy * 20;
	draw_line(main, main->player_data->px, main->player_data->py, line_x,
		line_y);
}

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

void	init_image(t_data *data, int width, int height)
{
	data->img = mlx_new_image(data->mlx_ptr, width, height);
	if (!data->img)
	{
		printf(ERR_NO_IMG); // free missing
		exit(1);
	}
	data->img_data = mlx_get_data_addr(data->img, &data->bpp, &data->size_line,
			&data->endian);
	if (!data->img_data)
	{
		printf(ERR_NO_IMG_DATA_ADDRESS); // free missing
		exit(1);
	}
}

void	render(t_main *main, int count)
{
	init_image(main->data, main->s_width, main->s_height);
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
		exit(1); // free missing
	}
	mlx_put_image_to_window(main->data->mlx_ptr, main->data->win_ptr,
		main->data->img, 0, 0);
	if (!main->data->img)
	{
		printf(ERR_IMG_CREATE_F);
		exit(1); // free missing
	}
	mlx_destroy_image(main->data->mlx_ptr, main->data->img);
}
