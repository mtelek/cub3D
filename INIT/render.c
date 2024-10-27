/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:57:41 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/27 21:24:11 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	draw_line(t_main *main, int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	err = dx - dy;
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	while (1)
	{
		mlx_pixel_put(main->data->mlx_ptr, main->data->win_ptr, x0, y0,
			PLAYER_COLOR);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = err * 2;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_player(void *mlx_ptr, void *win_ptr, t_main *main)
{
	int	x;
	int	y;
	// int	line_x;
	// int	line_y;

	y = -PLAYER_SIZE;
	while (y <= PLAYER_SIZE)
	{
		x = -PLAYER_SIZE;
		while (x <= PLAYER_SIZE)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, main->player_data->px + x,
				main->player_data->py + y, PLAYER_COLOR);
			x++;
		}
		y++;
	}
	// line_x = main->player_data->px + main->player_data->pdx * 20;
	// line_y = main->player_data->py + main->player_data->pdy * 20;
	// draw_line(main, main->player_data->px, main->player_data->py, line_x,
	// 	line_y);
}

void	render(void *mlx_ptr, void *win_ptr, t_main *main, int count)
{
	draw_map(main);
	if (count == 0)
		set_player_angle(main);
	draw_player(mlx_ptr, win_ptr, main);
	draw_rays_3d(main);
}
