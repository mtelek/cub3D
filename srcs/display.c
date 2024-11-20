/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:18:57 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/20 22:08:45 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	parse_res_helper(const char *resolution_str, int *i, int *temp_height,
		int *temp_width)
{
	static int	is_height;

	if (resolution_str[*i] == ',')
	{
		is_height = 1;
		return ;
	}
	if (!(is_height))
	{
		if (resolution_str[*i] >= '0' && resolution_str[*i] <= '9')
			*temp_width = *temp_width * 10 + (resolution_str[*i] - '0');
	}
	else
	{
		if (resolution_str[*i] >= '0' && resolution_str[*i] <= '9')
			*temp_height = *temp_height * 10 + (resolution_str[*i] - '0');
	}
}

void	parse_resolution(const char *resolution_str, t_main *main)
{
	int	i;
	int	temp_width;
	int	temp_height;

	i = 0;
	temp_width = 0;
	temp_height = 0;
	while (resolution_str[i] != '\0')
	{
		parse_res_helper(resolution_str, &i, &temp_height, &temp_width);
		i++;
	}
	main->s_width = temp_width;
	main->s_height = temp_height;
}

void	read_bytes(t_main *main, int fd, char *resolution, size_t buffer_size)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, resolution, buffer_size - 1);
	if (bytes_read > 0)
	{
		resolution[bytes_read] = '\0';
		parse_resolution(resolution, main);
		printf("Screen resolution: Width = %d, Height = %d\n", main->s_width,
			main->s_height);
	}
	else
	{
		printf(ERR_NO_RES);
		main->s_width = 800;
		main->s_height = 800;
	}
}

void	get_display_resolution(t_main *main)
{
	int		fd;
	char	resolution[100];

	fd = open("/syss/class/graphics/fb0/virtual_size", O_RDONLY);
	if (fd == -1)
	{
		printf(ERR_FRAME_BUFF);
		main->s_width = 800;
		main->s_height = 800;
		return ;
	}
	read_bytes(main, fd, resolution, sizeof(resolution));
	if (close(fd) == -1)
	{
		perror(ERR_CLOSE_FILE);
		free_function(main);
		exit(1);
	}
}
