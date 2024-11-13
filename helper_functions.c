/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:09:01 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/13 01:46:06 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/cub3D.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	printf("Map:\n");
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	print_textures(t_textures *textures)
{
	if (textures->floor)
		printf("Floor texture: %ls\n", (int *)textures->floor);
	else
		printf("Floor texture: (not found)\n");
	if (textures->ceiling)
		printf("Ceiling texture: %ls\n", (int *)textures->ceiling);
	else
		printf("Ceiling texture: (not found)\n");
}
