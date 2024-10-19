/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:54:56 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/20 00:10:06 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	render(void *mlx_ptr, void *win_ptr, t_main *main)
{
	mlx_clear_window(mlx_ptr, win_ptr);
	draw_map(main);
}

int	handle_keys(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	return (0);
}

int	init_mlx(t_main *main)
{
	Display	*display;
	Screen	*screen;
	int		screen_width;
	int		screen_height;

	display = XOpenDisplay(NULL);
	if (!display)
		return (printf(ERR_DISPLAY), 1);
	screen = DefaultScreenOfDisplay(display);
	screen_width = screen->width;
	screen_height = screen->height;
	main->data->mlx_ptr = mlx_init();
	if (!main->data->mlx_ptr)
		return (printf(ERR_INIT_MLX), 1);
	main->data->win_ptr = mlx_new_window(main->data->mlx_ptr, screen_width,
			screen_height, "cub3D");
	if (!main->data->win_ptr)
		return (printf(ERR_WINDOW), 1);
	render(main->data->mlx_ptr, main->data->win_ptr, main);
	mlx_key_hook(main->data->win_ptr, handle_keys, main->data);
	mlx_loop(main->data->mlx_ptr);
	XCloseDisplay(display);
	return (0);
}
