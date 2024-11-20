/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:50:58 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/20 20:16:25 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

int	init_data(t_main *main)
{
	main->data->keys[0] = 0;
	main->data->keys[1] = 0;
	main->data->keys[2] = 0;
	main->data->keys[3] = 0;
	main->data->fov = BASE_FOV * (main->s_width / main->s_height);
	main->data->angle_step = main->data->fov / main->pov;
	main->data->proj_plane_dist = main->s_width / (2 * tan(main->data->fov
				/ 2));
	main->data->d_ray = malloc(sizeof(float) * (main->pov + 1));
	if (!main->data->d_ray)
		return (printf(ERR_MF_D_RAY), free_function(main), 1);
	main->data->mlx_ptr = mlx_init();
	if (!main->data->mlx_ptr)
		return (printf(ERR_INIT_MLX), free_function(main), 1);
	main->data->win_ptr = mlx_new_window(main->data->mlx_ptr, main->s_width,
			main->s_height, "cub3D");
	if (!main->data->win_ptr)
		return (printf(ERR_WINDOW), mlx_destroy_display(main->data->mlx_ptr),
			free(main->data->mlx_ptr), free(main->data->d_ray),
			free_function(main), 1);
	main->data->speed = get_speed(main);
	return (0);
}

int	malloc_textures(t_main *main)
{
	main->textures->no = malloc(sizeof(t_texture));
	main->textures->so = malloc(sizeof(t_texture));
	main->textures->we = malloc(sizeof(t_texture));
	main->textures->ea = malloc(sizeof(t_texture));
	main->textures->ceiling = NULL;
	main->textures->floor = NULL;
	if (!main->textures->no || !main->textures->so || !main->textures->we
		|| !main->textures->ea)
		return (printf(ERR_MF_TEX), free_just_texts(main), 1);
	return (0);
}

int	init_structs(t_main *main)
{
	main->content = NULL;
	main->content_base = NULL;
	main->flag_changed = 0;
	main->textures = malloc(sizeof(t_textures));
	if (!main->textures)
		return (printf(ERR_MF_TEXTURES), 1);
	if (malloc_textures(main))
		return (1);
	main->data = (t_data *)malloc(sizeof(t_data));
	if (!main->data)
		return (printf(ERR_MF_DATA), free_just_texts(main), 1);
	main->map = malloc(sizeof(t_map));
	if (!main->map)
		return (printf(ERR_MF_MAP_S), free_just_texts(main),
			free(main->data), 1);
	main->player_data = (t_player_data *)malloc(sizeof(t_player_data));
	if (!main->player_data)
		return (printf(ERR_MF_PLAYER_D), free_just_texts(main),
			free(main->data),
			free(main->map), 1);
	return (0);
}
