/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_path_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:56:11 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/21 18:56:34 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

void	init_var_val_cont(int counts[6], int *i, int *j)
{
	int	k;

	*i = -1;
	*j = -1;
	k = -1;
	while (++k < 6)
		counts[k] = 0;
}

int	check_identifier(char *line, int *counts)
{
	if (!ft_strncmp(line, "NO", 2))
		return (++counts[0], 0);
	if (!ft_strncmp(line, "WE", 2))
		return (++counts[1], 0);
	if (!ft_strncmp(line, "SO", 2))
		return (++counts[2], 0);
	if (!ft_strncmp(line, "EA", 2))
		return (++counts[3], 0);
	if (!ft_strncmp(line, "F", 1))
		return (++counts[4], 0);
	if (!ft_strncmp(line, "C", 1))
		return (++counts[5], 0);
	return (1);
}

char	*skip_whitespace(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

int	validate_content(t_main *main)
{
	int		counts[6];
	int		i;
	int		j;
	char	*line;

	init_var_val_cont(counts, &i, &j);
	while (main->content[++i])
	{
		line = skip_whitespace(main->content[i]);
		if (*line == '\0')
			continue ;
		if (ft_strchr(line, '1') || ft_strchr(line, '0'))
			continue ;
		if (check_identifier(line, counts))
			return (printf("Error: Invalid or unexpected line '%s'\n", line),
				1);
	}
	while (++j < 6)
	{
		if (counts[j] > 1)
			return (printf("Error: Duplicate identifier found\n"), 1);
	}
	return (0);
}
