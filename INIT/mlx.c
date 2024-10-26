/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:54:56 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/27 00:59:21 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

int	is_wall(t_main *main, float new_px, float new_py)
{
	int	curr_x;
	int	curr_y;
	int	new_x;
	int	new_y;

	curr_x = (int)(main->player_data->px / main->map->mapS);
	curr_y = (int)(main->player_data->py / main->map->mapS);
	new_x = (int)(new_px / main->map->mapS);
	new_y = (int)(new_py / main->map->mapS);
	if (new_x < 0 || new_x >= main->map->mapX[new_y] || new_y < 0
		|| new_y >= main->map->mapY)
		return (1);
	if (main->map->map[new_y][new_x] == '1')
		return (1);
	if (curr_x != new_x && curr_y != new_y)
	{
		if (main->map->map[curr_y][new_x] == '1'
			|| main->map->map[new_y][curr_x] == '1')
			return (1);
	}
	if (curr_x != new_x && curr_y == new_y)
	{
		if ((curr_x < new_x && main->map->map[curr_y][curr_x + 1] == '1')
			|| (curr_x > new_x && main->map->map[curr_y][curr_x - 1] == '1'))
			return (1);
	}
	if (curr_y != new_y && curr_x == new_x)
	{
		if ((curr_y < new_y && main->map->map[curr_y + 1][curr_x] == '1')
			|| (curr_y > new_y && main->map->map[curr_y - 1][curr_x] == '1'))
			return (1);
	}
	return (0);
}

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
	int	line_x;
	int	line_y;

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
	line_x = main->player_data->px + main->player_data->pdx * 20;
	line_y = main->player_data->py + main->player_data->pdy * 20;
	draw_line(main, main->player_data->px, main->player_data->py, line_x,
		line_y);
}

void	update_direction(t_main *main, float angle)
{
	main->player_data->player_angle += angle;
	main->player_data->pdx = cos(main->player_data->player_angle);
	main->player_data->pdy = sin(main->player_data->player_angle);
}

int	handle_key_press(int keycode, t_main *main)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(main->data->mlx_ptr, main->data->win_ptr);
		exit(0);
	}
	if (keycode == 'w')
		main->data->keys[0] = 1;
	if (keycode == 'a')
		main->data->keys[1] = 1;
	if (keycode == 's')
		main->data->keys[2] = 1;
	if (keycode == 'd')
		main->data->keys[3] = 1;
	if (keycode == 65361)
		update_direction(main, -0.2);
	if (keycode == 65363)
		update_direction(main, +0.2);
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

	new_px = main->player_data->px;
	new_py = main->player_data->py;
	if (main->data->keys[0])
	{
		new_px += main->player_data->pdx * 5;
		new_py += main->player_data->pdy * 5;
	}
	if (main->data->keys[1])
	{
		new_px += main->player_data->pdy * 5;
		new_py -= main->player_data->pdx * 5;
	}
	if (main->data->keys[2])
	{
		new_px -= main->player_data->pdx * 5;
		new_py -= main->player_data->pdy * 5;
	}
	if (main->data->keys[3])
	{
		new_px -= main->player_data->pdy * 5;
		new_py += main->player_data->pdx * 5;
	}
	if (!is_wall(main, new_px, new_py))
	{
		main->player_data->px = new_px;
		main->player_data->py = new_py;
	}
	render(main->data->mlx_ptr, main->data->win_ptr, main, count);
	count++;
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

void	render(void *mlx_ptr, void *win_ptr, t_main *main, int count)
{
	draw_map(main);
	if (count == 0)
		set_player_angle(main);
	draw_player(mlx_ptr, win_ptr, main);
}

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
	main->data->mlx_ptr = mlx_init();
	if (!main->data->mlx_ptr)
		return (printf(ERR_INIT_MLX), 1);
	main->data->win_ptr = mlx_new_window(main->data->mlx_ptr, main->s_width,
			main->s_height, "cub3D");
	if (!main->data->win_ptr)
		return (printf(ERR_WINDOW), 1);
	init_keys(main);
	mlx_hook(main->data->win_ptr, 2, 1L << 0, handle_key_press, main);
	mlx_hook(main->data->win_ptr, 3, 1L << 1, handle_key_release, main);
	mlx_loop_hook(main->data->mlx_ptr, update_movement, main);
	mlx_loop(main->data->mlx_ptr);
	return (0);
}
