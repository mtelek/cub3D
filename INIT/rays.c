/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:20:58 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/27 21:36:00 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

float calc_ray_l(float px, float py, float rx, float ry)
{
    return (sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py)));
}

float normalize_angle(float angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}

void cast_single_ray(t_main *main, float ra)
{
    int dof;
    float rx, ry, xo, yo;
    int mx, my;
    float aTan = -1 / tan(ra);
    float nTan = -tan(ra);
    float vertical_ray = -1;
    float horizontal_ray = -1;
    float hit_rx = 0, hit_ry = 0;

    // Normalize angle for consistency
    ra = normalize_angle(ra);

    // Horizontal raycasting
    dof = 0;
    if (ra > M_PI) // Looking up
    {
        ry = ((int)(main->player_data->py) / (int)main->map->mapS) * main->map->mapS - 0.0001;
        rx = (main->player_data->py - ry) * aTan + main->player_data->px;
        yo = -main->map->mapS;
        xo = -yo * aTan;
    }
    else if (ra < M_PI) // Looking down
    {
        ry = ((int)(main->player_data->py) / (int)main->map->mapS) * main->map->mapS + main->map->mapS;
        rx = (main->player_data->py - ry) * aTan + main->player_data->px;
        yo = main->map->mapS;
        xo = -yo * aTan;
    }
    else // Looking straight left or right
    {
        rx = main->player_data->px;
        ry = main->player_data->py;
        dof = 8;
    }

    while (dof < 8)
    {
        mx = (int)(rx / main->map->mapS);
        my = (int)(ry / main->map->mapS);
        if (my < main->map->mapY && my >= 0 && mx >= 0 && mx < main->map->mapX[my] && main->map->map[my][mx] == '1') // Wall hit
        {
            horizontal_ray = calc_ray_l(main->player_data->px, main->player_data->py, rx, ry);
            break;
        }
        else
        {
            rx += xo;
            ry += yo;
            dof++;
        }
    }
    float h_rx = rx;
    float h_ry = ry;

    // Vertical raycasting
    dof = 0;
    if (ra > M_PI_2 && ra < 3 * M_PI_2) // Looking left
    {
        rx = ((int)(main->player_data->px) / (int)main->map->mapS) * main->map->mapS - 0.0001;
        ry = (main->player_data->px - rx) * nTan + main->player_data->py;
        xo = -main->map->mapS;
        yo = -xo * nTan;
    }
    else if (ra < M_PI_2 || ra > 3 * M_PI_2) // Looking right
    {
        rx = ((int)(main->player_data->px) / (int)main->map->mapS) * main->map->mapS + main->map->mapS;
        ry = (main->player_data->px - rx) * nTan + main->player_data->py;
        xo = main->map->mapS;
        yo = -xo * nTan;
    }
    else // Looking straight up or down
    {
        rx = main->player_data->px;
        ry = main->player_data->py;
        dof = 8;
    }

    while (dof < 8)
    {
        mx = (int)(rx / main->map->mapS);
        my = (int)(ry / main->map->mapS);
        if (my < main->map->mapY && my >= 0 && mx >= 0 && mx < main->map->mapX[my] && main->map->map[my][mx] == '1') // Wall hit
        {
            vertical_ray = calc_ray_l(main->player_data->px, main->player_data->py, rx, ry);
            break;
        }
        else
        {
            rx += xo;
            ry += yo;
            dof++;
        }
    }
    float v_rx = rx;
    float v_ry = ry;

    // Choose the shortest ray to draw
    if (horizontal_ray > 0 && (vertical_ray == -1 || horizontal_ray < vertical_ray))
    {
        hit_rx = h_rx;
        hit_ry = h_ry;
    }
    else if (vertical_ray > 0)
    {
        hit_rx = v_rx;
        hit_ry = v_ry;
    }

    // Draw only the shortest ray
    draw_line(main, (int)main->player_data->px, (int)main->player_data->py, (int)hit_rx, (int)hit_ry);
}

void draw_rays_3d(t_main *main)
{
    int num_rays = POV;  // Number of rays, one per degree
    float fov = M_PI / 3; // 60 degrees in radians
    float angle_step = fov / num_rays;
    float start_angle = normalize_angle(main->player_data->player_angle - fov / 2);

    for (int i = 0; i < num_rays; i++)
    {
        float ray_angle = normalize_angle(start_angle + i * angle_step);
        cast_single_ray(main, ray_angle);
    }
}
