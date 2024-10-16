/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:55:34 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/16 23:17:43 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/cub3D.h"

int	process_buffer(char *buffer, t_main *main, int *index)
{
	char	*line_start;
	char	*newline;

	line_start = buffer;
	newline = ft_strchr(line_start, '\n');
	while (newline != NULL)
	{
		*newline = '\0';
		main->content[*index] = ft_strdup(line_start);
		if (!main->content[*index])
			return (printf(ERR_MF_STRDUP), 1);
		(*index)++;
		line_start = newline + 1;
		newline = ft_strchr(line_start, '\n');
	}
	if (*line_start)
	{
		main->content[*index] = ft_strdup(line_start);
		if (!main->content[*index])
			return (printf(ERR_MF_STRDUP), 1);
		(*index)++;
	}
	return (0);
}

int	read_file(const char *filename, t_main *main)
{
	char	buffer[BUFFER_SIZE + 1];
	int		fd;
	int		bytes_read;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror(ERR_OPEN_FILE), 1);
	main->content = malloc(sizeof(char *) * MAX_LINES);
	if (!main->content)
		return (printf(ERR_MF_CONTENT), close(fd), 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (process_buffer(buffer, main, &i))
			return (close(fd), 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	main->content[i] = NULL;
	if (close(fd) == -1)
		return (perror(ERR_CLOSE_FILE), 1);
	return (0);
}

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
	main->textures->no = find_line(main, "NO", 2);
	main->textures->so = find_line(main, "SO", 2);
	main->textures->we = find_line(main, "WE", 2);
	main->textures->ea = find_line(main, "EA", 2);
	main->textures->floor = find_line(main, "F", 1);
	main->textures->ceiling = find_line(main, "C", 1);
	if (!main->textures->no || !main->textures->so || !main->textures->we
		|| !main->textures->ea || !main->textures->floor
		|| !main->textures->ceiling)
		return (free_after_split(main), printf(ERR_TEXTURE_MISSING), 1);
	if (init_map(main))
		return (free_function(main), 1);
	return (0);
}
