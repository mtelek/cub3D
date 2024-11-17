/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:20:58 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/17 21:33:38 by mtelek           ###   ########.fr       */
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

void	checking_length_by_square_hor(t_main *main, t_ray *ray)
{
	while (ray->dof < DOF_LIMIT)
	{
		ray->mx = (int)(ray->rx / main->map->mapS);
		ray->my = (int)(ray->ry / main->map->mapS);
		if (ray->my < main->map->mapY && ray->my >= 0 && ray->mx >= 0
			&& ray->mx < main->map->mapX[ray->my]
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
		ray->ry = ((int)(main->player_data->py) / (int)main->map->mapS)
			* main->map->mapS - 0.0001;
		ray->rx = (main->player_data->py - ray->ry) * ray->atan
			+ main->player_data->px;
		ray->yo = -main->map->mapS;
		ray->xo = -ray->yo * ray->atan;
	}
	else if (ray->ra < M_PI)
	{
		ray->ry = ((int)(main->player_data->py) / (int)main->map->mapS)
			* main->map->mapS + main->map->mapS;
		ray->rx = (main->player_data->py - ray->ry) * ray->atan
			+ main->player_data->px;
		ray->yo = main->map->mapS;
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
		ray->mx = (int)(ray->rx / main->map->mapS);
		ray->my = (int)(ray->ry / main->map->mapS);
		if (ray->my < main->map->mapY && ray->my >= 0 && ray->mx >= 0
			&& ray->mx < main->map->mapX[ray->my]
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
		ray->rx = ((int)(main->player_data->px) / (int)main->map->mapS)
			* main->map->mapS - 0.0001;
		ray->ry = (main->player_data->px - ray->rx) * ray->ntan
			+ main->player_data->py;
		ray->xo = -main->map->mapS;
		ray->yo = -ray->xo * ray->ntan;
	}
	else if (ray->ra < M_PI_2 || ray->ra > 3 * M_PI_2)
	{
		ray->rx = ((int)(main->player_data->px) / (int)main->map->mapS)
			* main->map->mapS + main->map->mapS;
		ray->ry = (main->player_data->px - ray->rx) * ray->ntan
			+ main->player_data->py;
		ray->xo = main->map->mapS;
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

void	choose_shortest_ray(t_ray *ray)
{
	if (ray->horizontal_ray > 0 && (ray->vertical_ray == -1
			|| ray->horizontal_ray < ray->vertical_ray))
	{
		ray->hit_rx = ray->h_rx;
		ray->hit_ry = ray->h_ry;
		if (ray->ra > M_PI)
			ray->wall_side = 'S';
		else
			ray->wall_side = 'N';
	}
	else if (ray->vertical_ray > 0)
	{
		ray->hit_rx = ray->v_rx;
		ray->hit_ry = ray->v_ry;
		if (ray->ra > M_PI_2 && ray->ra < 3 * M_PI_2)
			ray->wall_side = 'E';
		else
			ray->wall_side = 'W';
	}
}

t_ray	cast_single_ray(t_main *main, float ra, int i)
{
	t_ray	ray;

	init_ray_var(&ray, ra);
	ray.ra = normalize_angle(ra);
	calc_hor_ray(&ray, main);
	ray.dof = 0;
	if (ray.horizontal_ray == -1 || (ray.horizontal_ray > 1
			&& ray.horizontal_ray >= ray.vertical_ray))
		calc_ver_ray(&ray, main);
	choose_shortest_ray(&ray);
	main->data->d_ray[i] = calc_ray_l(main->player_data->px,
			main->player_data->py, ray.hit_rx, ray.hit_ry);
	draw_line(main, (int)main->player_data->px, (int)main->player_data->py,
		(int)ray.hit_rx, (int)ray.hit_ry);
	return (ray);
}

void	copy_pix_line(t_texture *text, char *temp_text, int y)
{
	int	x;
	int	byte;
	int	temp_offset;
	int	data_offset;

	x = text->width - 1;
	while (x >= 0)
	{
		byte = 0;
		while (byte < text->bpp / 8)
		{
			temp_offset = y * text->size_line + (text->width - x - 1)
				* (text->bpp / 8) + byte;
			data_offset = y * text->size_line + x * (text->bpp / 8) + byte;
			temp_text[temp_offset] = text->data[data_offset];
			byte++;
		}
		x--;
	}
}

void	reverse_texture(t_texture *text)
{
	char	*temp_text;
	int		y;

	temp_text = malloc(text->size_line * text->height);
	if (!temp_text)
	{
		printf(ERR_MF_TEMP_TEXT);
		exit(1); // proper freeing missing
	}
	y = -1;
	while (++y < text->height)
		copy_pix_line(text, temp_text, y);
	ft_memcpy(text->data, temp_text, text->size_line * text->height);
	free(temp_text);
}

void	put_floor_or_ceiling(char indicator, t_main *main, t_renray *renray)
{
	int	y;

	if (indicator == 'C')
	{
		y = -1;
		while (++y < renray->wall_top)
			put_pixel_to_image(main, renray->screen_x, y,
				main->textures->ceiling_color);
	}
	else if (indicator == 'F')
	{
		y = renray->wall_bottom - 1;
		while (++y < main->s_height)
			put_pixel_to_image(main, renray->screen_x, y,
				main->textures->floor_color);
	}
}

void	put_ray_to_img(t_main *main, t_ray *ray, t_renray *renray,
		t_texture *texture)
{
	int	y;
	int	tex_y;
	int	tex_x;
	int	color;

	put_floor_or_ceiling('C', main, renray);
	y = renray->wall_top - 1;
	while (++y < renray->wall_bottom)
	{
		tex_y = (y - renray->wall_top) * texture->height / renray->wall_height;
		if (ray->wall_side == 'N' || ray->wall_side == 'S')
			tex_x = fmod(ray->hit_rx * (texture->width / main->map->mapS),
					texture->width);
		else
			tex_x = fmod(ray->hit_ry * (texture->width / main->map->mapS),
					texture->width);
		color = *(int *)(texture->data + tex_y * texture->size_line + tex_x
				* (texture->bpp / 8));
		put_pixel_to_image(main, renray->screen_x, y, color);
	}
	put_floor_or_ceiling('F', main, renray);
}

t_texture	*choose_wall_side(t_ray ray, t_main *main)
{
	t_texture	*texture;

	if (ray.wall_side == 'N')
		texture = main->textures->no;
	else if (ray.wall_side == 'S')
		texture = main->textures->so;
	else if (ray.wall_side == 'W')
		texture = main->textures->we;
	else if (ray.wall_side == 'E')
		texture = main->textures->ea;
	return (texture);
}

void	draw_rays(t_main *main)
{
	int			x;
	t_ray		ray;
	t_renray	renray;
	t_texture	*texture;

	renray.start_angle = normalize_angle(main->player_data->player_angle
			- main->data->fov / 2);
	x = -1;
	while (++x < main->pov)
	{
		renray.ray_angle = normalize_angle(renray.start_angle + x
				* main->data->angle_step);
		ray = cast_single_ray(main, renray.ray_angle, x);
		renray.perpendicular_distance = main->data->d_ray[x]
			* cos(main->player_data->player_angle - renray.ray_angle);
		renray.wall_height = (main->map->mapS * main->data->proj_plane_dist)
			/ renray.perpendicular_distance;
		renray.wall_top = (main->s_height / 2) - (renray.wall_height / 2);
		renray.wall_bottom = renray.wall_top + renray.wall_height;
		renray.screen_x = (x * main->s_width) / main->pov;
		texture = choose_wall_side(ray, main);
		put_ray_to_img(main, &ray, &renray, texture);
	}
}
