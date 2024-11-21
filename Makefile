NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lmlx -lm -lXext -lX11
SRCDIR = .
OBJDIR = .objs
SRCS = main.c \
		srcs/calc_hor_ver_ray.c srcs/calc_map1.c srcs/calc_map2.c \
		srcs/display.c srcs/init_colors.c srcs/init_map.c srcs/init_structs.c \
		srcs/init_text.c srcs/map_check.c srcs/map_draw_player.c srcs/map_wall_check.c \
		srcs/mlx.c srcs/move_angle_speed.c srcs/move.c srcs/rays_text.c srcs/rays1.c srcs/rays2.c \
		srcs/read_file.c srcs/render.c srcs/text_path.c srcs/text_path_check.c \
		free1.c free2.c \
		Libft_utils/libft_utils1.c Libft_utils/libft_utils2.c\

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all : $(NAME)
bonus : $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean :
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all