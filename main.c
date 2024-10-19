/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:38:01 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/19 23:57:22 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/cub3D.h"

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
	if (init_main(&main))
		return (1);
	if (read_file(argv[1], &main))
		return (free(main.textures), 1);
	main.content_base = main.content;
	if (split_content(&main))
		return (1);
	init_mlx(&main);
	// print_textures(main.textures);
	// print_map(main.map);
	free_function(&main);
	return (0);
}
