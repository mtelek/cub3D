/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:54:55 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/16 00:52:59 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "error_messages.h"
# include <stdio.h>
# include <unistd.h>  
# include <stdlib.h>
# include <fcntl.h>

# define BUFFER_SIZE 4096
# define MAX_LINES 4096

typedef struct s_main
{
	char	**content;
	char	**content_base;
}	t_main;

//LIBFT_UTILS
char	*ft_strdup(const char *s1);

#endif