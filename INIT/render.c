/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:57:41 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/05 16:28:34 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void draw_line(t_main *main, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        put_pixel_to_image(main, x0, y0, PLAYER_COLOR);
        if (x0 == x1 && y0 == y1)
            break;
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


void draw_player(t_main *main)
{
    int x, y;
    int line_x;
    int line_y;

    for (y = -PLAYER_SIZE; y <= PLAYER_SIZE; y++)
    {
        for (x = -PLAYER_SIZE; x <= PLAYER_SIZE; x++)
        {
            int screen_x = main->player_data->px + x;
            int screen_y = main->player_data->py + y;
            if (screen_x >= 0 && screen_x < main->s_width && screen_y >= 0 && screen_y < main->s_height)
            {
                put_pixel_to_image(main, screen_x, screen_y, PLAYER_COLOR);
            }
        }
    }
    line_x = main->player_data->px + main->player_data->pdx * 20;
	line_y = main->player_data->py + main->player_data->pdy * 20;
	draw_line(main, main->player_data->px, main->player_data->py, line_x,
		line_y);
}

void put_pixel_to_image(t_main *main, int x, int y, int color)
{
    if (x >= 0 && x < main->s_width && y >= 0 && y < main->s_height)
    {
        char *pixel = main->data->img_data + (y * main->data->size_line + x * (main->data->bpp / 8));
        *(int*)pixel = color;
    }
}


void init_image(t_data *data, int width, int height)
{
    data->img = mlx_new_image(data->mlx_ptr, width, height);
    if (!data->img)
    {
        fprintf(stderr, "Failed to create image\n");
        exit(1);
    }
    data->img_data = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);
    if (!data->img_data)
    {
        fprintf(stderr, "Failed to get image data address\n");
        exit(1);
    }
}

void render(t_main *main, int count)
{
    init_image(main->data, main->s_width, main->s_height);
    calc_map(main);
	if (count == 0)
		set_player_angle(main);
    draw_rays(main);
    draw_map(main);
    draw_player(main);
	mlx_put_image_to_window(main->data->mlx_ptr, main->data->win_ptr, main->data->img, 0, 0);
    mlx_destroy_image(main->data->mlx_ptr, main->data->img);
}
