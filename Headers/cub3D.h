/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:54:55 by mtelek            #+#    #+#             */
/*   Updated: 2024/11/23 14:57:38 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "error_messages.h"
# include <X11/Xlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 4096
# define MAX_LINES 4096
# define PLAYER_COLOR 0xFFFF00
# define BASE_FOV 1.0471975511965976
# define COLOR_MAP_WALL 0x7D7F7D
# define COLOR_MAP_FLOOR 0x000000
# define DOF_LIMIT 150
# define FILE_EXT ".cub"

typedef struct s_line
{
	int				coords[4];
	int				deltas[2];
	int				steps[2];
	int				err;
}					t_line;

typedef struct s_renray
{
	float			start_angle;
	float			ray_angle;
	float			perpendicular_distance;
	float			wall_height;
	int				wall_top;
	int				wall_bottom;
	int				screen_x;
}					t_renray;

typedef struct s_ray
{
	int				dof;
	float			atan;
	float			ntan;
	float			rx;
	float			ry;
	float			xo;
	float			yo;
	int				mx;
	int				my;
	float			vertical_ray;
	float			horizontal_ray;
	float			hit_rx;
	float			hit_ry;
	float			ra;
	float			h_rx;
	float			h_ry;
	float			v_rx;
	float			v_ry;
	char			wall_side;
}					t_ray;

typedef struct s_player_data
{
	float			player_size;
	float			px;
	float			py;
	float			player_angle;
	float			pdx;
	float			pdy;
	char			direction;

}					t_player_data;

typedef struct s_map
{
	char			**map;
	float			map_s;
	int				map_y;
	int				*map_x;
}					t_map;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	float			*d_ray;
	int				keys[4];
	float			angle_step;
	float			proj_plane_dist;
	void			*img;
	char			*img_data;
	int				bpp;
	int				size_line;
	int				endian;
	float			speed;
	float			fov;
}					t_data;

typedef struct s_texture
{
	void			*img;
	char			*path;
	int				width;
	int				height;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_texture;

typedef struct s_textures
{
	t_texture		*no;
	t_texture		*so;
	t_texture		*we;
	t_texture		*ea;
	char			*floor;
	char			*ceiling;
	int				floor_color;
	int				ceiling_color;
}					t_textures;

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

// CALC_HOR_VER_RAY
void				checking_length_by_square_hor(t_main *main, t_ray *ray);
void				calc_hor_ray(t_ray *ray, t_main *main);
void				checking_length_by_square_ver(t_main *main, t_ray *ray);
void				calc_ver_ray(t_ray *ray, t_main *main);

// CALC_MAP1
int					find_biggest_x(t_main *main);
void				calc_map_s(t_main *main);
void				calc_player_pos(t_main *main);
void				map_check_failed(t_main *main);
void				calc_map(t_main *main);

// CALC_MAP2
void				count_column(t_main *main, int row);
void				count_row(t_main *main);

// DISPLAY
void				parse_res_helper(const char *resolution_str, int *i,
						int *temp_height, int *temp_width);
void				parse_resolution(const char *resolution_str, t_main *main);
void				read_bytes(t_main *main, int fd, char *resolution,
						size_t buffer_size);
void				get_display_resolution(t_main *main);

// INIT_COLORS
int					rgb_to_hex(const char *rgb_str, int *r, int *g,
						t_main *main);
void				init_floor_and_ceiling_colors(t_textures *textures,
						t_main *main);

// INIT_MAPS
void				draw_rectangle(t_main *main, int x, int y, int color);
void				draw_map(t_main *main);
int					init_map(t_main *main);

// INIT_STRUCTS
int					init_data(t_main *main);
int					init_structs(t_main *main);

// INIT_TEXT
void				cleanup_textures(t_data *data, t_textures *textures);
void				init_img(t_data *data, t_textures *textures, t_main *main);
void				init_text_data(t_textures *textures, t_main *main);
void				init_textures(t_data *data, t_textures *textures,
						t_main *main);

// MAP_CHECK
int					check_lines(char *line, int end, char **map, int i);
int					check_first_last_line(char *line);
int					check_chars(t_main *main);
int					map_check(t_main *main);

// MAP_DRAW_PLAYER
void				draw_line(t_main *main, int line_x, int line_y);
void				draw_player(t_main *main);

// MAP_WALL_CHECK
int					is_position_wall(t_main *main, float px, float py);
int					is_diagonal_wall(t_main *main, int curr_x, int curr_y,
						int new_pos[2]);
int					is_linear_wall(t_main *main, int curr_x, int curr_y,
						int new_pos[2]);
int					is_wall(t_main *main, float new_px, float new_py);

// MLX
void				create_mlx_hooks(t_main *main);
int					init_mlx(t_main *main);

// MOVE_ANGLE_SPEED
float				get_speed(t_main *main);
void				update_direction(t_main *main, float angle);
void				set_player_angle(t_main *main);

// MOVE
void				check_wasd(int keycode, t_main *main);
int					handle_key_press(int keycode, t_main *main);
int					handle_key_release(int keycode, t_main *main);
void				check_keys(t_main *main, float *new_px, float *new_py);
int					update_movement(t_main *main);

// RAYS_TEXT
void				copy_pix_line(t_texture *text, char *temp_text, int y);
void				reverse_texture(t_texture *text, t_main *main);
t_texture			*choose_wall_side(t_ray ray, t_main *main);

// RAYS1
void				choose_shortest_ray(t_ray *ray);
t_ray				cast_single_ray(t_main *main, float ra, int i);
void				put_floor_or_ceiling(char indicator, t_main *main,
						t_renray *renray);
void				put_ray_to_img(t_main *main, t_ray *ray, t_renray *renray,
						t_texture *texture);
void				draw_rays(t_main *main);

// RAYS2
float				calc_ray_l(float px, float py, float rx, float ry);
float				normalize_angle(float angle);
void				init_ray_var(t_ray *ray, float ra);

// READ_FILE
int					process_buffer(char *buffer, t_main *main, int *index);
int					read_file(const char *filename, t_main *main);

// RENDER
void				put_pixel_to_image(t_main *main, int x, int y, int color);
void				init_image(t_data *data, int width, int height,
						t_main *main);
void				render(t_main *main, int count);

// TEXT_PATH_CHECK
void				init_var_val_cont(int counts[6], int *i, int *j);
int					check_identifier(char *line, int *counts);
char				*skip_whitespace(char *line);
int					validate_content(t_main *main);

// TEXT_PATH
char				*find_line(t_main *main, char *to_find, int length);
int					split_content(t_main *main);

// FREE
int					exit_at_closing(t_main *main);
void				exit_function(t_main *main, int exit_code);
void				free_init_main(t_main *main);
void				free_function(t_main *main);
void				free_after_split(t_main *main);
void				free_just_texts(t_main *main);
void				free_before_split(t_main *main);

// FREE2
void				free_textures(t_main *main);
void				free_map(t_main *main);
void				free_content(t_main *main);

// LIBFT_UTILS
size_t				ft_strlen(const char *str);
int					ft_atoi(const char *str);
char				*ft_strtok(char *str, char sepa);
char				*ft_strchr(const char *str, int c);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				*ft_strdup(const char *s1);
int					ft_strcmp(char *s1, char *s2);
int					ft_isspace(int c);
int					ft_isdigit(int c);

#endif