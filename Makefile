NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = .
OBJDIR = .objs
SRCS = main.c 


OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all : $(NAME)

$(NAME): $(OBJS)
			@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

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