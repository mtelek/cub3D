/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:50:58 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/13 20:46:53 by mtelek           ###   ########.fr       */
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

int rgb_to_hex(const char *rgb_str, int *r, int *g, int *b)
{
    char *token;
    char *rgb_copy;

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

void init_floor_and_ceiling_colors(t_main *main)
{
	int r;
	int g;
	int b;

	r = -1;
	g = -1;
	b = -1;
    if (main->textures->floor)
        main->textures->floor_color = rgb_to_hex(main->textures->floor, &r, &g, &b);
    if (main->textures->ceiling)
        main->textures->ceiling_color = rgb_to_hex(main->textures->ceiling, &r, &g, &b);
}

void init_textures(t_main *main)
{
    main->textures->no->img = mlx_xpm_file_to_image(main->data->mlx_ptr, main->textures->no->path, &main->textures->no->width, &main->textures->no->height);
    main->textures->so->img = mlx_xpm_file_to_image(main->data->mlx_ptr, main->textures->so->path, &main->textures->so->width, &main->textures->so->height);
    main->textures->we->img = mlx_xpm_file_to_image(main->data->mlx_ptr, main->textures->we->path, &main->textures->we->width, &main->textures->we->height);
    main->textures->ea->img = mlx_xpm_file_to_image(main->data->mlx_ptr, main->textures->ea->path, &main->textures->ea->width, &main->textures->ea->height);
    if (!main->textures->no->img || !main->textures->so->img || !main->textures->we->img || !main->textures->ea->img)
    {
        printf(ERR_LOAD_TEX);
        exit(1); // Add appropriate error handling here
    }
    main->textures->no->data = mlx_get_data_addr(main->textures->no->img, &main->textures->no->bpp, &main->textures->no->size_line, &main->textures->no->endian);
	main->textures->so->data = mlx_get_data_addr(main->textures->so->img, &main->textures->so->bpp, &main->textures->so->size_line, &main->textures->so->endian);
	main->textures->we->data = mlx_get_data_addr(main->textures->we->img, &main->textures->we->bpp, &main->textures->we->size_line, &main->textures->we->endian);
	main->textures->ea->data = mlx_get_data_addr(main->textures->ea->img, &main->textures->ea->bpp, &main->textures->ea->size_line, &main->textures->ea->endian);
	 if (!main->textures->no->data || !main->textures->so->data || !main->textures->we->data || !main->textures->ea->data)
    {
        printf(ERR_NO_TEX_DATA);
        exit(1); // Add appropriate error handling here
    }
	reverse_texture(main->textures->no);
	reverse_texture(main->textures->ea);
	init_floor_and_ceiling_colors(main);
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
	if (!main->textures->no || !main->textures->so || !main->textures->we || !main->textures->ea)
		return (printf(ERR_MF_TEX), 1);
	main->data = (t_data *)malloc(sizeof(t_data));
	if (!main->data)
		return (printf(ERR_MF_DATA), 1);
	main->map = malloc(sizeof(t_map));
	if (!main->map)
		return (printf(ERR_MF_MAP_S), 1);
	main->player_data = (t_player_data *)malloc(sizeof(t_player_data));
	if (!main->player_data)
		return (printf(ERR_MF_PLAYER_D), 1);
	return (0);
}
