/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:05:14 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/23 14:12:45 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

int	rgb_to_hex(const char *rgb_str, int *r, int *g, t_main *main)
{
	char	*token;
	char	*rgb_copy;
	int		b;

	b = -1;
	rgb_copy = ft_strdup(rgb_str);
	token = ft_strtok(rgb_copy, ',');
	if (token != NULL)
		*r = ft_atoi(token);
	token = ft_strtok(NULL, ',');
	if (token != NULL)
		*g = ft_atoi(token);
	token = ft_strtok(NULL, ',');
	if (token != NULL)
		b = ft_atoi(token);
	free(rgb_copy);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || b < 0 || b > 255)
	{
		printf(ERR_INV_RGB);
		exit_function(main, 1);
	}
	return ((*r << 16) | (*g << 8) | b);
}

void	init_floor_and_ceiling_colors(t_textures *textures, t_main *main)
{
	int	r;
	int	g;

	r = -1;
	g = -1;
	if (textures->floor)
		textures->floor_color = rgb_to_hex(textures->floor, &r, &g, main);
	if (textures->ceiling)
		textures->ceiling_color = rgb_to_hex(textures->ceiling, &r, &g, main);
}
