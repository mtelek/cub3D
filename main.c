/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:38:01 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/18 00:13:35 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/cub3D.h"

void	render(void *mlx_ptr, void *win_ptr)
{
	mlx_clear_window(mlx_ptr, win_ptr);
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
		return (printf("Failed to open X display\n"), 1);
	screen = DefaultScreenOfDisplay(display);
	screen_width = screen->width;
	screen_height = screen->height;
	main->data->mlx_ptr = mlx_init();
	if (!main->data->mlx_ptr)
		return (printf("Error initializing MLX\n"), 1);
	main->data->win_ptr = mlx_new_window(main->data->mlx_ptr, screen_width,
			screen_height, "cub3D");
	if (!main->data->win_ptr)
		return (printf("Error creating window\n"), 1);
	render(main->data->mlx_ptr, main->data->win_ptr);
	mlx_key_hook(main->data->win_ptr, handle_keys, main->data);
	mlx_loop(main->data->mlx_ptr);
	XCloseDisplay(display);
	return (0);
}

int	argc_check(int argc)
{
	if (argc < 2)
		return (printf(ERR_NO_MAP), 1);
	if (argc > 2)
		return (printf(ERR_TOO_MANY_ARGS), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (argc_check(argc))
		return (1);
	if (init_main(&main))
		return (1);
	if (read_file(argv[1], &main))
		return (free(main.textures), 1);
	main.content_base = main.content;
	if (split_content(&main))
		return (1);
	init_mlx(&main);
	// print_textures(main.textures);
	// print_map(main.map);
	free_function(&main);
	return (0);
}
