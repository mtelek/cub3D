/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:54:56 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/22 01:39:32 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

float px = 1000;
float py = 500;

#define PLAYER_SIZE 5
#define PLAYER_COLOR 0xFFFF00 

void draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, color);
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
    int x, y;

    for (y = -PLAYER_SIZE; y <= PLAYER_SIZE; y++)
    {
        for (x = -PLAYER_SIZE; x <= PLAYER_SIZE; x++)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, px + x, py + y, PLAYER_COLOR);
        }
    }
    int line_x = px + main->data->pdx * 20;
    int line_y = py + main->data->pdy * 20;
    draw_line(mlx_ptr, win_ptr, px, py, line_x, line_y, PLAYER_COLOR);
}

void update_direction(t_main *main)
{
    main->data->pdx = cos(main->data->player_angle);
    main->data->pdy = sin(main->data->player_angle); 
}

int handle_key_press(int keycode, t_main *main)
{
    if (keycode == 65307)
    {
        mlx_destroy_window(main->data->mlx_ptr, main->data->win_ptr);
        exit(0);
    }
    if (keycode == 'w')
        main->data->keys[0] = 1;  // W key pressed
    if (keycode == 'a')
        main->data->keys[1] = 1;  // A key pressed
    if (keycode == 's')
        main->data->keys[2] = 1;  // S key pressed
    if (keycode == 'd')
        main->data->keys[3] = 1;  // D key pressed
    if (keycode == 65361)
    {
        main->data->player_angle += 0.3;
        update_direction(main);
    }
    if (keycode == 65363)
    {
        main->data->player_angle -= 0.3;
        update_direction(main);
    }
    return (0);
}

int handle_key_release(int keycode, t_main *main)
{
    if (keycode == 'w')
        main->data->keys[0] = 0;  // W key released
    if (keycode == 'a')
        main->data->keys[1] = 0;  // A key released
    if (keycode == 's')
        main->data->keys[2] = 0;  // S key released
    if (keycode == 'd')
        main->data->keys[3] = 0;  // D key released
    return (0);
}

int update_movement(t_main *main)
{
    if (main->data->keys[0])  // W key (Move forward relative to the player's angle)
    {
        px += main->data->pdx * 5;
        py += main->data->pdy * 5;
    }
    if (main->data->keys[1])  // A key (Strafe left, perpendicular to the player's angle)
    {
        px -= main->data->pdy * 5;
        py += main->data->pdx * 5;
    }
    if (main->data->keys[2])  // S key (Move backward relative to the player's angle)
    {
        px -= main->data->pdx * 5;
        py -= main->data->pdy * 5;
    }
    if (main->data->keys[3])  // D key (Strafe right, perpendicular to the player's angle)
    {
        px += main->data->pdy * 5;
        py -= main->data->pdx * 5;
    }
    mlx_clear_window(main->data->mlx_ptr, main->data->win_ptr);
    render(main->data->mlx_ptr, main->data->win_ptr, main);

    return (0);  // Must return 0 for mlx_loop_hook
}


void render(void *mlx_ptr, void *win_ptr, t_main *main)
{
    mlx_clear_window(mlx_ptr, win_ptr);
    draw_map(main);
    draw_player(mlx_ptr, win_ptr, main);
}

int init_mlx(t_main *main)
{
    Display *display;
    Screen *screen;
    int screen_width;
    int screen_height;

    display = XOpenDisplay(NULL);
    if (!display)
        return (printf(ERR_DISPLAY), 1);
    screen = DefaultScreenOfDisplay(display);
    screen_width = screen->width;
    screen_height = screen->height;
    main->data->mlx_ptr = mlx_init();
    if (!main->data->mlx_ptr)
        return (printf(ERR_INIT_MLX), 1);
    main->data->win_ptr = mlx_new_window(main->data->mlx_ptr, screen_width, screen_height, "cub3D");
    if (!main->data->win_ptr)
        return (printf(ERR_WINDOW), 1);
    mlx_hook(main->data->win_ptr, 2, 1L<<0, handle_key_press, main);
    mlx_hook(main->data->win_ptr, 3, 1L<<1, handle_key_release, main);
    mlx_loop_hook(main->data->mlx_ptr, update_movement, main);
    mlx_loop(main->data->mlx_ptr);
    XCloseDisplay(display);
    return (0);
}
