/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:38:01 by mtelek            #+#    #+#             */
/*   Updated: 2025/07/23 14:38:08 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3D.h"

int	file_type_check(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (printf(ERR_WRONG_F_TYPE), 1);
	if (ft_strcmp(&filename[len - 4], FILE_EXT) != 0)
		return (printf(ERR_WRONG_F_TYPE), 1);
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

int	main(int argc, char **argv)
{
	t_main	main;

	if (argc_check(argc))
		return (1);
	if (file_type_check(argv[1]))
		return (1);
	if (init_structs(&main))
		return (1);
	if (read_file(argv[1], &main))
		return (1);
	main.content_base = main.content;
	if (split_content(&main))
		return (1);
	if (init_mlx(&main))
		return (1);
	return (0);
}
