/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:52:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/23 14:17:23 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/cub3D.h"

int	exit_at_closing(t_main *main)
{
	cleanup_textures(main->data, main->textures);
	mlx_destroy_window(main->data->mlx_ptr, main->data->win_ptr);
	mlx_destroy_display(main->data->mlx_ptr);
	free(main->data->mlx_ptr);
	free(main->data->d_ray);
	free_function(main);
	exit(0);
}

void	exit_function(t_main *main, int exit_code)
{
	cleanup_textures(main->data, main->textures);
	mlx_destroy_window(main->data->mlx_ptr, main->data->win_ptr);
	mlx_destroy_display(main->data->mlx_ptr);
	free(main->data->mlx_ptr);
	free(main->data->d_ray);
	free_function(main);
	exit(exit_code);
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
