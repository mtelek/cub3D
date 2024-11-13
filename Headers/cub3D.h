/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:54:55 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/13 02:02:16 by mtelek           ###   ########.fr       */
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
# include <X11/Xlib.h>
# include <mlx.h>

# define BUFFER_SIZE 4096
# define MAX_LINES 4096
# define PLAYER_COLOR 0xFFFF00
# define BASE_FOV (M_PI / 3.0f)

typedef struct s_ray
{
	int dof;
	float atan;
	float ntan;
	float rx;
	float ry;
	float xo;
	float yo;
	int mx;
	int my;
	float vertical_ray;
	float horizontal_ray;
	float hit_rx;
	float hit_ry;
	float ra;
	float h_rx;
	float h_ry;
	float v_rx;
	float v_ry;
	char wall_side;
}	t_ray;

typedef struct s_player_data
{
	float	player_size;
	float	px;
	float	py;
	float	player_angle;
	float	pdx;
	float	pdy;
	char	direction;
	
}	t_player_data;

typedef struct s_map
{
	char		**map;
	float		mapS;
	int			mapY;
	int			*mapX;
}				t_map;

typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
    float   *d_ray;
    int     keys[4];
	float	angle_step;
	float	proj_plane_dist;
    void    *img;
    char    *img_data;
    int     bpp;
    int     size_line;
    int     endian;
	float	speed;
	float	fov; //could put it together with pov
}               t_data;

typedef struct s_texture {
    void    *img;
    char    *path;
    int     width;
    int     height;
    char     *data;
    int     bpp;
    int     size_line;
    int     endian;
}				t_texture;

typedef struct s_textures
{
	t_texture	*no;
	t_texture	*so;
	t_texture	*we;
	t_texture	*ea;
	char	*floor;
	char	*ceiling;
	int		floor_color;
	int		ceiling_color;
}			t_textures;

typedef struct s_main
{
	char			**content;
	char			**content_base;
	int				s_width;
    int				s_height;
	int				flag_changed;
	int				pov;
	float			player_size;
	t_textures		*textures;
	t_data			*data;
	t_map			*map;
	t_player_data	*player_data;
}					t_main;

//INIT
int		init_main(t_main *main);
void 	init_textures(t_main *main);
int		init_map(t_main *main);
int		process_buffer(char *buffer, t_main *main, int *index);
int		read_file(const char *filename, t_main *main);
char	*find_line(t_main *main, char *to_find, int length);
int		split_content(t_main *main);

//MAP_CHECK
int		map_check(t_main *main);
int		is_wall(t_main *main, float new_px, float new_py);

//MAP
void	calc_map(t_main *main);
void	draw_map(t_main *main);

//MLX
int		init_mlx(t_main *main);
void	render(t_main *main, int count);
void 	put_pixel_to_image(t_main *main, int x, int y, int color);

//TEXTURE
void 	reverse_texture(t_texture *text);

//MOVEMENT
int		handle_key_press(int keycode, t_main *main);
int		handle_key_release(int keycode, t_main *main);
int		update_movement(t_main *main);
void	set_player_angle(t_main *main);

//RAYS
void 	draw_rays(t_main *main);
void	draw_line(t_main *main, int x0, int y0, int x1, int y1);

//DISPLAY
void	get_display_resolution(t_main *main);

//FREE
void	free_function(t_main *main);
void	free_after_split(t_main *main);

//LIBFT_UTILS
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strchr(const char *str, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strtok(char *str, char sepa);
int		ft_atoi(const char *str);

//HELPER_FUNCTIONS
void	print_textures(t_textures *textures);
void	print_map(char **map);

#endif