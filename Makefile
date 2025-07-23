NAME = cub3D
CC = cc

MLX_DIR = minilibx-linux-master
MLX_INC = -I$(MLX_DIR)
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

CFLAGS = -Wall -Wextra -Werror $(MLX_INC) -g
LDFLAGS = $(MLX_LIB)

SRCDIR = srcs
OBJDIR = .objs
SRCS = main.c calc_hor_ver_ray.c calc_map1.c calc_map2.c \
        display.c init_colors.c init_map.c init_structs.c \
        init_text.c map_check.c map_draw_player.c map_wall_check.c \
        mlx.c move_angle_speed.c move.c rays_text.c rays1.c rays2.c \
        read_file.c render.c text_path.c text_path_check.c \
        free1.c free2.c libft_utils1.c libft_utils2.c
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: mlx $(NAME)
mlx: $(MLX_DIR)/libmlx.a

$(MLX_DIR)/libmlx.a:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "\033[31mError: $(MLX_DIR) missing!\033[0m"; \
		echo "Download with: git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)"; \
		exit 1; \
	elif [ ! -f "$(MLX_DIR)/libmlx.a" ] || [ -n "$$(find $(MLX_DIR) -newer $(MLX_DIR)/libmlx.a)" ]; then \
		echo "\033[33mCompiling MinilibX...\033[0m"; \
		$(MAKE) -C $(MLX_DIR) clean; \
		$(MAKE) -C $(MLX_DIR); \
	else \
		echo "\033[32mMinilibX up-to-date\033[0m"; \
	fi

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "\033[32m✓ $(NAME) compiled successfully\033[0m"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)
	@echo "\033[32m✓ Cleaned object files\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[32m✓ Full clean completed\033[0m"

re: fclean all
