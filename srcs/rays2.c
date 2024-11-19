/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:27:46 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/19 17:27:59 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

float	calc_ray_l(float px, float py, float rx, float ry)
{
	return (sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py)));
}

float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	init_ray_var(t_ray *ray, float ra)
{
	ray->dof = 0;
	ray->atan = -1 / tan(ra);
	ray->ntan = -tan(ra);
	ray->vertical_ray = -1;
	ray->horizontal_ray = -1;
	ray->hit_rx = 0;
	ray->hit_ry = 0;
}
