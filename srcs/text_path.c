/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:01:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/23 14:42:29 by mtelek           ###   ########.fr       */
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

int	is_valid_f_c_line(char *line)
{
	int	i;
	int	comma_count;
	int	digit_count;

	i = 0;
	comma_count = 0;
	digit_count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma_count++;
		else if (line[i] == '+' || line[i] == '-')
		{
			if (i > 0 && line[i - 1] != ',' && !ft_isspace(line[i - 1]))
				return (1);
		}
		else if (ft_isdigit(line[i]))
			digit_count++;
		else if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	if (comma_count != 2 || digit_count == 0)
		return (1);
	return (0);
}

int	f_c_check(t_main *main)
{
	if (is_valid_f_c_line(main->textures->floor))
		return (printf(ERR_BAD_F), 1);
	else if (is_valid_f_c_line(main->textures->ceiling))
		return (printf(ERR_BAD_C), 1);
	else
		return (0);
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
	if (f_c_check(main))
		return (free_after_split(main), 1);
	if (init_map(main))
		return (free_function(main), 1);
	return (0);
}
