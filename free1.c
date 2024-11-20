/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:52:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/20 20:14:20 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/cub3D.h"

void	exit_function(t_main *main)
{
	cleanup_textures(main->data, main->textures);
	mlx_destroy_window(main->data->mlx_ptr, main->data->win_ptr);
	mlx_destroy_display(main->data->mlx_ptr);
	free(main->data->mlx_ptr);
	free(main->data->d_ray);
	free_function(main);
	exit(1);
}

void	free_init_main(t_main *main)
{
	free_just_texts(main);
	free(main->data);
	free(main->map);
	free(main->player_data);
}

void	free_function(t_main *main)
{
	free_content(main);
	free(main->data);
	free(main->player_data);
	free_textures(main);
	free_map(main);
}

void	free_after_split(t_main *main)
{
	free_content(main);
	free(main->data);
	free(main->map);
	free(main->player_data);
	free_textures(main);
}
