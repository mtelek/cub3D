/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:09:01 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/09 21:06:04 by mtelek           ###   ########.fr       */
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

//void	print_textures(t_textures *textures)
//{
//	if (textures->no->path)
//		printf("NO texture: %s\n", textures->no->path);
//	else
//		printf("NO texture: (not found)\n");
//	if (textures->so->path)
//		printf("SO texture: %s\n", textures->so->path);
//	else
//		printf("SO texture: (not found)\n");
//	if (textures->we->path)
//		printf("WE texture: %s\n", textures->we->path);
//	else
//		printf("WE texture: (not found)\n");
//	if (textures->ea->path)
//		printf("EA texture: %s\n", textures->ea->path);
//	else
//		printf("EA texture: (not found)\n");
//	if (textures->floor)
//		printf("Floor texture: %s\n", textures->floor);
//	else
//		printf("Floor texture: (not found)\n");
//	if (textures->ceiling)
//		printf("Ceiling texture: %s\n", textures->ceiling);
//	else
//		printf("Ceiling texture: (not found)\n");
//}
