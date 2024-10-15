/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:38:01 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/16 00:58:18 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/cub3D.h"

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
		main->content[i] = ft_strdup(buffer);
		if (!main->content[i++])
			return (printf(ERR_MF_STRDUP), close(fd), 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	main->content[i] = '\0';
	if (close(fd) == -1)
		return (perror(ERR_CLOSE_FILE), 1);
	return (0);
}

int	argc_check(int argc)
{
	if (argc < 2)
		return (printf(ERR_NO_MAP), 1);
	if (argc > 2)
		return (printf(ERR_TOO_MANY_ARGS), 1);
	return (0);
}

int	init_main(t_main *main)
{
	main->content = NULL;
	main->content_base = NULL;
	return (0);
}

void	free_function(t_main *main)
{
	if (main->content_base)
	{
		free(main->content_base);
		main->content_base = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (argc_check(argc))
		return (1);
	init_main(&main);
	if (read_file(argv[1], &main))
		return (1);
	main.content_base = main.content;
	while (*main.content)
	{
		printf("%s", *main.content);
		free(*main.content);
		main.content++;
	}
	free_function(&main);
	return (0);
}
