/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:50:58 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/17 23:05:23 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

int	init_map(t_main *main)
{
	int	i;
	int	map_index;

	i = 0;
	while (main->content[i] && (main->content[i][0] != '0'
		&& main->content[i][0] != '1' && main->content[i][0] != ' '))
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
	main->map->map[map_index] = NULL;
	return (0);
}

int	rgb_to_hex(const char *rgb_str, int *r, int *g, int *b)
{
	char	*token;
	char	*rgb_copy;

	rgb_copy = ft_strdup(rgb_str);
	token = ft_strtok(rgb_copy, ',');
	if (token != NULL)
		*r = ft_atoi(token);
	token = ft_strtok(NULL, ',');
	if (token != NULL)
		*g = ft_atoi(token);
	token = ft_strtok(NULL, ',');
	if (token != NULL)
		*b = ft_atoi(token);
	free(rgb_copy);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
	{
		printf(ERR_INV_RGB);
		exit(1); // Free any other resources here if needed
	}
	return ((*r << 16) | (*g << 8) | *b);
}

void	init_floor_and_ceiling_colors(t_textures *textures)
{
	int	r;
	int	g;
	int	b;

	r = -1;
	g = -1;
	b = -1;
	if (textures->floor)
		textures->floor_color = rgb_to_hex(textures->floor, &r, &g, &b);
	if (textures->ceiling)
		textures->ceiling_color = rgb_to_hex(textures->ceiling, &r, &g, &b);
}

void	init_img(t_data *data, t_textures *textures)
{
	textures->no->img = mlx_xpm_file_to_image(data->mlx_ptr, textures->no->path,
			&textures->no->width, &textures->no->height);
	textures->so->img = mlx_xpm_file_to_image(data->mlx_ptr, textures->so->path,
			&textures->so->width, &textures->so->height);
	textures->we->img = mlx_xpm_file_to_image(data->mlx_ptr, textures->we->path,
			&textures->we->width, &textures->we->height);
	textures->ea->img = mlx_xpm_file_to_image(data->mlx_ptr, textures->ea->path,
			&textures->ea->width, &textures->ea->height);
	if (!textures->no->img || !textures->so->img || !textures->we->img
		|| !textures->ea->img)
	{
		printf(ERR_LOAD_TEX);
		exit(1); // Add appropriate error handling here
	}
}

void	init_text_data(t_textures *textures)
{
	textures->no->data = mlx_get_data_addr(textures->no->img,
			&textures->no->bpp, &textures->no->size_line,
			&textures->no->endian);
	textures->so->data = mlx_get_data_addr(textures->so->img,
			&textures->so->bpp, &textures->so->size_line,
			&textures->so->endian);
	textures->we->data = mlx_get_data_addr(textures->we->img,
			&textures->we->bpp, &textures->we->size_line,
			&textures->we->endian);
	textures->ea->data = mlx_get_data_addr(textures->ea->img,
			&textures->ea->bpp, &textures->ea->size_line,
			&textures->ea->endian);
	if (!textures->no->data || !textures->so->data || !textures->we->data
		|| !textures->ea->data)
	{
		printf(ERR_NO_TEX_DATA);
		exit(1); // Add appropriate error handling here
	}
}

void	init_textures(t_data *data, t_textures *textures)
{
	init_img(data, textures);
	init_text_data(textures);
	reverse_texture(textures->no);
	reverse_texture(textures->ea);
	init_floor_and_ceiling_colors(textures);
}

int	init_main(t_main *main)
{
	main->content = NULL;
	main->content_base = NULL;
	main->flag_changed = 0;
	main->textures = malloc(sizeof(t_textures));
	if (!main->textures)
		return (printf(ERR_MF_TEXTURES), 1);
	main->textures->no = malloc(sizeof(t_texture));
	main->textures->so = malloc(sizeof(t_texture));
	main->textures->we = malloc(sizeof(t_texture));
	main->textures->ea = malloc(sizeof(t_texture));
	main->textures->ceiling = NULL;
	main->textures->floor = NULL;
	if (!main->textures->no || !main->textures->so || !main->textures->we
		|| !main->textures->ea)
		return (printf(ERR_MF_TEX), free_textures(main), 1);
	main->data = (t_data *)malloc(sizeof(t_data));
	if (!main->data)
		return (printf(ERR_MF_DATA), free_textures(main), 1);
	main->map = malloc(sizeof(t_map));
	if (!main->map)
		return (printf(ERR_MF_MAP_S), free_textures(main), free(main->data), 1);
	main->player_data = (t_player_data *)malloc(sizeof(t_player_data));
	if (!main->player_data)
		return (printf(ERR_MF_PLAYER_D), free_textures(main), free(main->data), free(main->map), 1);
	return (0);
}
