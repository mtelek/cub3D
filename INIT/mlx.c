/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:54:56 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/22 20:37:39 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

float px = 1000;
float py = 500;

void draw_line(t_main *main, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        mlx_pixel_put(main->data->mlx_ptr, main->data->win_ptr, x0, y0, PLAYER_COLOR);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = err * 2;
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

void draw_player(void *mlx_ptr, void *win_ptr, t_main *main)
{
    int x;
    int y;
    int line_x;
    int line_y;

    y = -PLAYER_SIZE;
    while (y <= PLAYER_SIZE)
    {
        x = -PLAYER_SIZE;
        while (x <= PLAYER_SIZE)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, px + x, py + y, PLAYER_COLOR);
            x++;
        }
        y++;
    }
    line_x = px + main->data->pdx * 20;
    line_y = py + main->data->pdy * 20;
    draw_line(main, px, py, line_x, line_y);
}

void update_direction(t_main *main, float angle)
{
    main->data->player_angle += angle;
    main->data->pdx = cos(main->data->player_angle);
    main->data->pdy = sin(main->data->player_angle); 
    mlx_clear_window(main->data->mlx_ptr, main->data->win_ptr);
    render(main->data->mlx_ptr, main->data->win_ptr, main);
}

int handle_key_press(int keycode, t_main *main)
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
        update_direction(main, -0.3);
    if (keycode == 65363)
        update_direction(main, +0.3);
    return (0);
}

int handle_key_release(int keycode, t_main *main)
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

int update_movement(t_main *main)
{
    if (main->data->keys[0])
    {
        px += main->data->pdx * 5;
        py += main->data->pdy * 5;
    }
    if (main->data->keys[1])
    {
        px += main->data->pdy * 5;
        py -= main->data->pdx * 5;
    }
    if (main->data->keys[2])
    {
        px -= main->data->pdx * 5;
        py -= main->data->pdy * 5;
    }
    if (main->data->keys[3])
    {
        px -= main->data->pdy * 5;
        py += main->data->pdx * 5;
    }
    if (main->data->keys[0] || main->data->keys[1] || main->data->keys[2] || main->data->keys[3])
    {
        mlx_clear_window(main->data->mlx_ptr, main->data->win_ptr);
        render(main->data->mlx_ptr, main->data->win_ptr, main);
    }
    return (0);
}

void render(void *mlx_ptr, void *win_ptr, t_main *main)
{
    mlx_clear_window(mlx_ptr, win_ptr);
    draw_map(main);
    draw_player(mlx_ptr, win_ptr, main);
}

void init_keys(t_main *main)
{
    main->data->keys[0] = 0;
    main->data->keys[1] = 0;
    main->data->keys[2] = 0;
    main->data->keys[3] = 0;
}

int init_mlx(t_main *main)
{
    get_display_resolution(main);
    main->data->mlx_ptr = mlx_init();
    if (!main->data->mlx_ptr)
        return (printf(ERR_INIT_MLX), 1);
    main->data->win_ptr = mlx_new_window(main->data->mlx_ptr, main->s_width, main->s_height, "cub3D");
    if (!main->data->win_ptr)
        return (printf(ERR_WINDOW), 1);
    init_keys(main);
    mlx_hook(main->data->win_ptr, 2, 1L<<0, handle_key_press, main);
    mlx_hook(main->data->win_ptr, 3, 1L<<1, handle_key_release, main);
    mlx_loop_hook(main->data->mlx_ptr, update_movement, main);
    mlx_loop(main->data->mlx_ptr);
    return (0);
}
