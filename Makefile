NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -I/mnt/c/Users/marci/minilibx-linux
LDFLAGS = -L/mnt/c/Users/marci/minilibx-linux -lmlx -lm -lXext -lX11
SRCDIR = .
OBJDIR = .objs
SRCS = main.c init.c init2.c free.c \
		Libft_utils/libft_utils1.c \
		helper_functions.c \

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all : $(NAME)

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