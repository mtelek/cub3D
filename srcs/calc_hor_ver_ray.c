/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_hor_ver_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:24:05 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/20 19:51:33 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	checking_length_by_square_hor(t_main *main, t_ray *ray)
{
	while (ray->dof < DOF_LIMIT)
	{
		ray->mx = (int)(ray->rx / main->map->map_s);
		ray->my = (int)(ray->ry / main->map->map_s);
		if (ray->my < main->map->map_y && ray->my >= 0 && ray->mx >= 0
			&& ray->mx < main->map->map_x[ray->my]
			&& main->map->map[ray->my][ray->mx] == '1')
		{
			ray->horizontal_ray = calc_ray_l(main->player_data->px,
					main->player_data->py, ray->rx, ray->ry);
			break ;
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

void	calc_hor_ray(t_ray *ray, t_main *main)
{
	if (ray->ra > M_PI)
	{
		ray->ry = ((int)(main->player_data->py) / (int)main->map->map_s)
			* main->map->map_s - 0.0001;
		ray->rx = (main->player_data->py - ray->ry) * ray->atan
			+ main->player_data->px;
		ray->yo = -main->map->map_s;
		ray->xo = -ray->yo * ray->atan;
	}
	else if (ray->ra < M_PI)
	{
		ray->ry = ((int)(main->player_data->py) / (int)main->map->map_s)
			* main->map->map_s + main->map->map_s;
		ray->rx = (main->player_data->py - ray->ry) * ray->atan
			+ main->player_data->px;
		ray->yo = main->map->map_s;
		ray->xo = -ray->yo * ray->atan;
	}
	else
	{
		ray->rx = main->player_data->px;
		ray->ry = main->player_data->py;
		ray->dof = DOF_LIMIT;
	}
	checking_length_by_square_hor(main, ray);
}

void	checking_length_by_square_ver(t_main *main, t_ray *ray)
{
	while (ray->dof < DOF_LIMIT)
	{
		ray->mx = (int)(ray->rx / main->map->map_s);
		ray->my = (int)(ray->ry / main->map->map_s);
		if (ray->my < main->map->map_y && ray->my >= 0 && ray->mx >= 0
			&& ray->mx < main->map->map_x[ray->my]
			&& main->map->map[ray->my][ray->mx] == '1')
		{
			ray->vertical_ray = calc_ray_l(main->player_data->px,
					main->player_data->py, ray->rx, ray->ry);
			break ;
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

void	calc_ver_ray(t_ray *ray, t_main *main)
{
	if (ray->ra > M_PI_2 && ray->ra < 3 * M_PI_2)
	{
		ray->rx = ((int)(main->player_data->px) / (int)main->map->map_s)
			* main->map->map_s - 0.0001;
		ray->ry = (main->player_data->px - ray->rx) * ray->ntan
			+ main->player_data->py;
		ray->xo = -main->map->map_s;
		ray->yo = -ray->xo * ray->ntan;
	}
	else if (ray->ra < M_PI_2 || ray->ra > 3 * M_PI_2)
	{
		ray->rx = ((int)(main->player_data->px) / (int)main->map->map_s)
			* main->map->map_s + main->map->map_s;
		ray->ry = (main->player_data->px - ray->rx) * ray->ntan
			+ main->player_data->py;
		ray->xo = main->map->map_s;
		ray->yo = -ray->xo * ray->ntan;
	}
	else
	{
		ray->rx = main->player_data->px;
		ray->ry = main->player_data->py;
		ray->dof = DOF_LIMIT;
	}
	checking_length_by_square_ver(main, ray);
}
