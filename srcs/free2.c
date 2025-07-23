/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:01:57 by mtelek            #+#    #+#             */
/*   Updated: 2025/07/23 14:37:47 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	free_before_split(t_main *main)
{
	free_content(main);
	free(main->data);
	free(main->map);
	free(main->player_data);
	free_just_texts(main);
}

void	free_just_texts(t_main *main)
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
		free(main->textures);
		main->textures = NULL;
	}
}

void	free_textures(t_main *main)
{
	if (main->textures)
	{
		if (main->textures->no->path)
			free(main->textures->no->path);
		if (main->textures->so->path)
			free(main->textures->so->path);
		if (main->textures->we->path)
			free(main->textures->we->path);
		if (main->textures->ea->path)
			free(main->textures->ea->path);
		if (main->textures->floor)
			free(main->textures->floor);
		if (main->textures->ceiling)
			free(main->textures->ceiling);
		if (main->textures->no)
			free(main->textures->no);
		if (main->textures->so)
			free(main->textures->so);
		if (main->textures->we)
			free(main->textures->we);
		if (main->textures->ea)
			free(main->textures->ea);
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
			main->map->map = NULL;
		}
		if (main->map->map_x)
		{
			free(main->map->map_x);
			main->map->map_x = NULL;
		}
		if (main->map)
		{
			free(main->map);
			main->map = NULL;
		}
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
