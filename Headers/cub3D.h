/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:54:55 by mtelek            #+#    #+#             */
/*   Updated: 2024/10/22 00:31:52 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "error_messages.h"
# include <stdio.h>
# include <unistd.h>  
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
#include "/mnt/c/Users/marci/minilibx-linux/mlx.h"
#include <X11/Xlib.h>

# define BUFFER_SIZE 4096
# define MAX_LINES 4096
# define MAP_S 64

typedef struct s_map
{
	char		**map;
	int			mapS;
	int			mapY;
	int			*mapX;

}				t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		keys[4];
	float	player_angle;
	float	pdx;
	float	pdy;
}				t_data;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor;
	char	*ceiling;
}			t_textures;

typedef struct s_main
{
	char		**content;
	char		**content_base;
	t_textures	*textures;
	t_data		*data;
	t_map		*map;
}				t_main;

//INIT
int		init_main(t_main *main);
void	init_textures(t_textures *textures);
int		init_map(t_main *main);
int		process_buffer(char *buffer, t_main *main, int *index);
int		read_file(const char *filename, t_main *main);
char	*find_line(t_main *main, char *to_find, int length);
int		split_content(t_main *main);

//MAP_CHECK
int		map_check(t_main *main);

//MAP
void	draw_map(t_main *main);

//MLX
int		init_mlx(t_main *main);
void	render(void *mlx_ptr, void *win_ptr, t_main *main);

//FREE
void	free_function(t_main *main);
void	free_after_split(t_main *main);

//LIBFT_UTILS
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strchr(const char *str, int c);

//HELPER_FUNCTIONS
void	print_textures(t_textures *textures);
void	print_map(char **map);

#endif