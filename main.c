/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:38:01 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/19 20:58:02 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/cub3D.h"

int	check_lines(char *line, int end)
{
	if (line[0] == 0)
		return (1);
	if (line[end] == 0)
		return (1);
	return (0);
}

int	check_first_last_line(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '0')
			return (1);
	}
	return (0);
}
int	map_check(t_main *main)
{
	char **map;
	int i;
	
	i = 0;
	map = main->map->map;
	if (check_first_last_line(map[0]) == 1)
		return (1);
	if (check_first_last_line(map[main->map->mapY - 1]) == 1)
		return (1);
	while (map[++i])
	{
		if (check_lines(map[i], main->map->mapX[i]) == 1)
			return (1);
	}
	return (0);
}

void	count_column(t_main *main, int row)
{
	int i;

	i = 0;
	while (main->map->map[row][i])
		i++;
	main->map->mapX[row] = i;
}

void	count_row(t_main *main)
{
	int i;

	i = 0;
	while (main->map->map[i])
	{
		count_column(main, i);
		i++;
	}
	main->map->mapY = i;
}

void	draw_rectangle(t_main *main, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while  (++i < main->map->mapS)
	{
		j = -1;
		while (++j < main->map->mapS)
			mlx_pixel_put(main->data->mlx_ptr, main->data->win_ptr, x + i, y + j, color);
	}
}

void	draw_map(t_main *main)
{
	int x;
	int y;
	int xo;
	int yo;

	count_row(main);
	if (map_check(main) == 1)
	{
		free_function(main);
		printf("Error: invalid map\n");
		exit (1);
	}
	main->map->mapS = MAP_S;
	y = -1;
	while (++y < main->map->mapY)
	{
		x = -1;
		while (++x < main->map->mapX[y])
		{
			xo = x * main->map->mapS;
			yo = y * main->map->mapS;
			if (main->map->map[y][x] == '1')
				draw_rectangle(main, xo, yo, 0xFFFFFF); // White
			else
				draw_rectangle(main, xo, yo, 0x000000); // Black
		}
	}
}

void	render(void *mlx_ptr, void *win_ptr, t_main *main)
{
	mlx_clear_window(mlx_ptr, win_ptr);
	draw_map(main);
}

int	handle_keys(int keycode, t_data *data, t_main *main)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free_function(main);
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
