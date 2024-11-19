/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:52:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/17 23:38:23 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/cub3D.h"

void	free_textures(t_main *main)
{
	if (main->textures)
	{
		if (main->textures->no)
			free(main->textures->no);
		if (main->textures->so)
			free(main->textures->so);
		if (main->textures->we)
			free(main->textures->we);
		if (main->textures->ea)
			free(main->textures->ea);
		if (main->textures->floor)
			free(main->textures->floor);
		if (main->textures->ceiling)
			free(main->textures->ceiling);
		free(main->textures);
		main->textures = NULL;
	}
}

void	free_map(t_main *main)
{
	int	i;

	i = -1;
	if (main->map)
	{
		if (main->map->map)
		{
			while (main->map->map[++i])
				free(main->map->map[i]);
			free(main->map->map);
		}
		if (main->map->mapX)
			free(main->map->mapX);
		free(main->map);
		main->map = NULL;
	}
}

void	free_content(t_main *main)
{
	int	i;

	i = -1;
	if (main->content)
	{
		while (main->content[++i])
			free(main->content[i]);
		free(main->content);
		main->content = NULL;
	}
}

void	free_init_main(t_main *main)
{
	free_textures(main);
	free(main->data);
	free(main->map);
	free(main->player_data);
}

void	free_function(t_main *main)
{
	free_textures(main);
	free(main->data);
	free(main->map);
	free(main->player_data); //till here init_main
	free_content(main);
	free_map(main);
}

void	free_after_split(t_main *main)
{
	free_content(main);
	free_textures(main);
}
