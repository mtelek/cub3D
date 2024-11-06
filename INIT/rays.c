/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:20:58 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/06 18:02:52 by mtelek           ###   ########.fr       */
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
    return (angle);
}

void    init_ray_var(t_ray *ray, float ra)
{
    ray->dof = 0;
    ray->atan = -1 / tan(ra);
    ray->ntan = -tan(ra);
    ray->vertical_ray = -1;
    ray->horizontal_ray = -1;
    ray->hit_rx = 0;
    ray->hit_ry = 0;
}

void calc_hor_ray(t_ray *ray, t_main *main)
{
     if (ray->ra > M_PI) // Looking up
    {
        ray->ry = ((int)(main->player_data->py) / (int)main->map->mapS) * main->map->mapS - 0.0001;
        ray->rx = (main->player_data->py - ray->ry) * ray->atan + main->player_data->px;
        ray->yo = -main->map->mapS;
        ray->xo = -ray->yo * ray->atan;
    }
    else if (ray->ra < M_PI) // Looking down
    {
        ray->ry = ((int)(main->player_data->py) / (int)main->map->mapS) * main->map->mapS + main->map->mapS;
        ray->rx = (main->player_data->py - ray->ry) * ray->atan + main->player_data->px;
        ray->yo = main->map->mapS;
        ray->xo = -ray->yo * ray->atan;
    }
    else // Looking straight left or right
    {
        ray->rx = main->player_data->px;
        ray->ry = main->player_data->py;
        ray->dof = 150;
    }
    while (ray->dof < 150)
    {
        ray->mx = (int)(ray->rx / main->map->mapS);
        ray->my = (int)(ray->ry / main->map->mapS);
        if (ray->my < main->map->mapY && ray->my >= 0 && ray->mx >= 0 && ray->mx < main->map->mapX[ray->my] && main->map->map[ray->my][ray->mx] == '1') // Wall hit
        {
            ray->horizontal_ray = calc_ray_l(main->player_data->px, main->player_data->py, ray->rx, ray->ry);
            break;
        }
        else
        {
            ray->rx += ray->xo;
            ray->ry += ray->yo;
            ray->dof++;
        }
    }
    ray->h_rx = ray->rx;
    ray->h_ry = ray->ry;
}

void    calc_ver_ray(t_ray *ray, t_main *main)
{
    ray->dof = 0;
    if (ray->ra > M_PI_2 && ray->ra < 3 * M_PI_2) // Looking left
    {
        ray->rx = ((int)(main->player_data->px) / (int)main->map->mapS) * main->map->mapS - 0.0001;
        ray->ry = (main->player_data->px - ray->rx) * ray->ntan + main->player_data->py;
        ray->xo = -main->map->mapS;
        ray->yo = -ray->xo * ray->ntan;
    }
    else if (ray->ra < M_PI_2 || ray->ra > 3 * M_PI_2) // Looking right
    {
        ray->rx = ((int)(main->player_data->px) / (int)main->map->mapS) * main->map->mapS + main->map->mapS;
        ray->ry = (main->player_data->px - ray->rx) * ray->ntan + main->player_data->py;
        ray->xo = main->map->mapS;
        ray->yo = -ray->xo * ray->ntan;
    }
    else // Looking straight up or down
    {
        ray->rx = main->player_data->px;
        ray->ry = main->player_data->py;
        ray->dof = 150;
    }
    while (ray->dof < 150)
    {
        ray->mx = (int)(ray->rx / main->map->mapS);
        ray->my = (int)(ray->ry / main->map->mapS);
        if (ray->my < main->map->mapY && ray->my >= 0 && ray->mx >= 0 && ray->mx < main->map->mapX[ray->my] && main->map->map[ray->my][ray->mx] == '1') // Wall hit
        {
            ray->vertical_ray = calc_ray_l(main->player_data->px, main->player_data->py, ray->rx, ray->ry);
            break;
        }
        else
        {
            ray->rx += ray->xo;
            ray->ry += ray->yo;
            ray->dof++;
        }
    }
    ray->v_rx = ray->rx;
    ray->v_ry = ray->ry;
}

void    choose_shortest_ray(t_ray *ray)
{
    if (ray->horizontal_ray > 0 && (ray->vertical_ray == -1 || ray->horizontal_ray < ray->vertical_ray))
    {
        ray->hit_rx = ray->h_rx;
        ray->hit_ry = ray->h_ry;
    }
    else if (ray->vertical_ray && ray->vertical_ray > 0)
    {
        ray->hit_rx = ray->v_rx;
        ray->hit_ry = ray->v_ry;
    }
}

void cast_single_ray(t_main *main, float ra, int i)
{
    t_ray ray;

    init_ray_var(&ray, ra);
    ray.ra = normalize_angle(ra);
    calc_hor_ray(&ray, main);
    if (ray.horizontal_ray == -1 || (ray.horizontal_ray > 1 && ray.horizontal_ray >= ray.vertical_ray))
        calc_ver_ray(&ray, main);
    choose_shortest_ray(&ray);
    main->data->d_ray[i] = calc_ray_l(main->player_data->px, main->player_data->py, ray.hit_rx, ray.hit_ry);
    draw_line(main, (int)main->player_data->px, (int)main->player_data->py, (int)ray.hit_rx, (int)ray.hit_ry);
}

void draw_rays(t_main *main)
{
    float start_angle = normalize_angle(main->player_data->player_angle - FOV / 2);
    
    for (int x = 0; x < main->pov; x++)
    {
        float ray_angle = normalize_angle(start_angle + x * main->data->angle_step);
        cast_single_ray(main, ray_angle, x);
        float c_dis = main->data->d_ray[x] * cos(main->player_data->player_angle - ray_angle);
        float wall_height = (main->map->mapS * main->data->proj_plane_dist) / c_dis;
        int wall_top = (main->s_height / 2) - (wall_height / 2);
        int wall_bottom = wall_top + wall_height;
        int screen_x = (x * main->s_width) / main->pov;
        for (int y = 0; y < wall_top; y++) {
            put_pixel_to_image(main, screen_x, y, CEILING_COLOR);
        }
        for (int y = wall_top; y < wall_bottom; y++) {
            put_pixel_to_image(main, screen_x, y, 0x808080);
        }
        for (int y = wall_bottom; y < main->s_height; y++)
            put_pixel_to_image(main, screen_x, y, FLOOR_COLOR);
    }
}
