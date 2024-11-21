/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:20:58 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/21 16:45:09 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

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
	draw_line(main, ray.hit_rx, ray.hit_ry);
	return (ray);
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

	if (ray->wall_side == 'N' || ray->wall_side == 'S')
		tex_x = fmod(ray->hit_rx * (texture->width / main->map->map_s),
				texture->width);
	else
		tex_x = fmod(ray->hit_ry * (texture->width / main->map->map_s),
				texture->width);
	put_floor_or_ceiling('C', main, renray);
	y = renray->wall_top - 1;
	while (++y < renray->wall_bottom && y < main->s_height)
	{
		if (y < 0)
			continue ;
		tex_y = (y - renray->wall_top) * texture->height / renray->wall_height;
		color = *(int *)(texture->data + tex_y * texture->size_line + tex_x
				* (texture->bpp / 8));
		put_pixel_to_image(main, renray->screen_x, y, color);
	}
	put_floor_or_ceiling('F', main, renray);
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
		renray.wall_height = (main->map->map_s * main->data->proj_plane_dist)
			/ renray.perpendicular_distance;
		renray.wall_top = (main->s_height / 2) - (renray.wall_height / 2);
		renray.wall_bottom = renray.wall_top + renray.wall_height;
		renray.screen_x = (x * main->s_width) / main->pov;
		texture = choose_wall_side(ray, main);
		put_ray_to_img(main, &ray, &renray, texture);
	}
}
