/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:50:58 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/16 23:14:52 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/cub3D.h"

int	init_map(t_main *main)
{
	int	i;
	int	map_index;

	i = 0;
	while (main->content[i] && (main->content[i][0] != '0'
		&& main->content[i][0] != '1'))
		i++;
	main->map = malloc(sizeof(char *) * (MAX_LINES - i));
	if (!main->map)
		return (printf(ERR_MF_MAP), 1);
	map_index = 0;
	while (main->content[i])
	{
		main->map[map_index] = ft_strdup(main->content[i]);
		if (!main->map[map_index])
			return (printf(ERR_MF_MAP_LINE), 1);
		map_index++;
		i++;
	}
	main->map[map_index] = '\0';
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
	return (0);
}
