/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:50:58 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/20 13:57:52 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	spaces_to_zeros(t_main *main)
{
	int	i;
	int	j;

	i = -1;
	while (main->map->map[++i])
	{
		j = -1;
		while (main->map->map[i][++j])
		{
			if (main->map->map[i][j] == ' ')
				main->map->map[i][j] = '0';
		}
	}
}

int	init_map(t_main *main)
{
	int	i;
	int	map_index;

	i = 0;
	while (main->content[i] && (main->content[i][0] != '0'
		&& main->content[i][0] != '1'))
		i++;
	main->map->map = malloc(sizeof(char *) * (MAX_LINES - i));
	if (!main->map->map)
		return (printf(ERR_MF_MAP), 1);
	main->map->mapX = malloc(sizeof(int) * (MAX_LINES - i));
	if (!main->map->mapX)
		return (printf(ERR_MF_MAPX), 1);
	map_index = 0;
	while (main->content[i])
	{
		main->map->map[map_index] = ft_strdup(main->content[i]);
		if (!main->map->map[map_index])
			return (printf(ERR_MF_MAP_LINE), 1);
		map_index++;
		i++;
	}
	main->map->map[map_index] = '\0';
	spaces_to_zeros(main);
	return (0);
}

void	init_textures(t_textures *textures)
{
	textures->no = NULL;
	textures->so = NULL;
	textures->we = NULL;
	textures->ea = NULL;
	textures->floor = NULL;
	textures->ceiling = NULL;
}

int	init_main(t_main *main)
{
	main->content = NULL;
	main->content_base = NULL;
	main->textures = malloc(sizeof(t_textures));
	if (!main->textures)
		return (printf(ERR_MF_TEXTURES), 1);
	init_textures(main->textures);
	main->data = malloc(sizeof(t_data));
	if (!main->data)
		return (printf(ERR_MF_DATA), 1);
	main->map = malloc(sizeof(t_map));
	if (!main->map)
		return (printf(ERR_MF_MAP_S), 1);
	return (0);
}
