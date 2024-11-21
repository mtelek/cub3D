/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:01:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/21 18:56:39 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

char	*find_line(t_main *main, char *to_find, int length)
{
	int		i;
	char	*line;
	char	*value_start;

	i = -1;
	while (main->content[++i])
	{
		if (!ft_strncmp(to_find, main->content[i], length))
		{
			line = main->content[i];
			value_start = line + length;
			while (*value_start == ' ' || *value_start == '\t')
				value_start++;
			return (ft_strdup(value_start));
		}
	}
	return (NULL);
}

int	split_content(t_main *main)
{
	if (validate_content(main))
		return (free_before_split(main), 1);
	main->textures->no->path = find_line(main, "NO", 2);
	main->textures->so->path = find_line(main, "SO", 2);
	main->textures->we->path = find_line(main, "WE", 2);
	main->textures->ea->path = find_line(main, "EA", 2);
	main->textures->floor = find_line(main, "F", 1);
	main->textures->ceiling = find_line(main, "C", 1);
	if (!main->textures->no->path || !main->textures->so->path
		|| !main->textures->we->path || !main->textures->ea->path
		|| !main->textures->floor || !main->textures->ceiling)
		return (free_after_split(main), printf(ERR_TEXTURE_MISSING), 1);
	if (init_map(main))
		return (free_function(main), 1);
	return (0);
}
