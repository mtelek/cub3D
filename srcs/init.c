/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:50:58 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/11 21:47:27 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	spaces_to_zeros(t_main *main)
{
	int	i;
	int	j;
	int	convert_spaces;

	i = -1;
	while (main->map->map[++i])
	{
		j = -1;
		convert_spaces = 0;
		while (main->map->map[i][++j])
		{
			if (!convert_spaces && (main->map->map[i][j] == '1' || main->map->map[i][j] == '0'))
				convert_spaces = 1;
			if (convert_spaces && main->map->map[i][j] == ' ')
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
	//spaces_to_zeros(main);
	return (0);
}

void init_textures(t_main *main)
{
    main->textures->no->img = mlx_xpm_file_to_image(main->data->mlx_ptr, main->textures->no->path, &main->textures->no->width, &main->textures->no->height);
    main->textures->so->img = mlx_xpm_file_to_image(main->data->mlx_ptr, main->textures->so->path, &main->textures->so->width, &main->textures->so->height);
    main->textures->we->img = mlx_xpm_file_to_image(main->data->mlx_ptr, main->textures->we->path, &main->textures->we->width, &main->textures->we->height);
    main->textures->ea->img = mlx_xpm_file_to_image(main->data->mlx_ptr, main->textures->ea->path, &main->textures->ea->width, &main->textures->ea->height);
    if (!main->textures->no->img || !main->textures->so->img || !main->textures->we->img || !main->textures->ea->img)
    {
        printf("Error loading textures\n");
        exit(1); // Add appropriate error handling here
    }
    main->textures->no->data = (int *)mlx_get_data_addr(main->textures->no->img, &main->textures->no->bpp, &main->textures->no->size_line, &main->textures->no->endian);
    main->textures->so->data = (int *)mlx_get_data_addr(main->textures->so->img, &main->textures->so->bpp, &main->textures->so->size_line, &main->textures->so->endian);
    main->textures->we->data = (int *)mlx_get_data_addr(main->textures->we->img, &main->textures->we->bpp, &main->textures->we->size_line, &main->textures->we->endian);
    main->textures->ea->data = (int *)mlx_get_data_addr(main->textures->ea->img, &main->textures->ea->bpp, &main->textures->ea->size_line, &main->textures->ea->endian);
	main->textures->floor = NULL;
	main->textures->ceiling = NULL;
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
		return (printf("Error allocating memory for textures"), 1); //proper one missing
	main->data = (t_data *)malloc(sizeof(t_data));
	if (!main->data)
		return (printf(ERR_MF_DATA), 1);
	main->map = malloc(sizeof(t_map));
	if (!main->map)
		return (printf(ERR_MF_MAP_S), 1);
	main->player_data = (t_player_data *)malloc(sizeof(t_player_data));
	if (!main->player_data)
		return (1); // error message missing
	return (0);
}
