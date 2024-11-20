/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:55:34 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/20 20:15:45 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

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
			return (printf(ERR_MF_STRDUP), free_init_main(main),
				free_content(main), 1);
		(*index)++;
		line_start = newline + 1;
		newline = ft_strchr(line_start, '\n');
	}
	if (*line_start)
	{
		main->content[*index] = ft_strdup(line_start);
		if (!main->content[*index])
			return (printf(ERR_MF_STRDUP), free_init_main(main),
				free_content(main), 1);
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
		return (perror(ERR_OPEN_FILE), free_init_main(main), 1);
	main->content = malloc(sizeof(char *) * MAX_LINES);
	if (!main->content)
		return (printf(ERR_MF_CONTENT), close(fd), free_init_main(main), 1);
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
		return (perror(ERR_CLOSE_FILE), free_init_main(main),
			free_content(main), 1);
	return (0);
}
